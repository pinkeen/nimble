#include "spriteengine.h"

SpriteEngine::SpriteEngine(Configurator *pConfig, AnimationManager *pAnimManager, Input *pInput,
	     TimerManager *pTimerManager, BoundingShapeManager *pBoundingShapeManager)
	: m_pConfig(pConfig), m_viewSize(pConfig->screenWidth(), pConfig->screenHeight())

{
	m_pGraphics = m_pConfig->graphics();
	m_pAnimManager = pAnimManager;
	m_pTimerManager = pTimerManager;
	m_pInput = pInput;
	m_pBoundingShapeManager = pBoundingShapeManager;
	m_drawBounds = false;

	setViewPos(Vec(0.0f, 0.0f));
}

SpriteEngine::~SpriteEngine()
{
	for(SpritePIterator it = m_spritesQueue.begin();
	    it != m_spritesQueue.end(); ++it)
		delete *it;
}

void SpriteEngine::commitNewSprites()
{
	for(SpritePIterator it = m_spritesQueue.begin();
	    it != m_spritesQueue.end(); ++it)
		m_sprites.addSprite(*it);

	m_spritesQueue.clear();
}

void SpriteEngine::registerSprite(Sprite *pSprite)
{
	m_spritesQueue.push_back(pSprite);
}

void SpriteEngine::updateSprites(float lag)
{
	SpriteContainer::Iterator it = m_sprites.iterator();

	while(it.next())
	{
		Sprite *s = it.item();

		s->step(lag);
		s->updateAnimation(lag);
	}
}

void SpriteEngine::commitKilled()
{
	SpriteContainer::Iterator it = m_sprites.iterator();

	while(it.next())
	{
		Sprite *s = it.item();

		if(s->killed())
		{
			it.removeItem();
		}
	}
}

void SpriteEngine::step(float lag)
{
	updateSprites(lag);
	processCollisions();
	commitKilled();
	commitNewSprites();
}

void SpriteEngine::draw()
{
	SpriteContainer::Iterator it = m_sprites.iterator();

	while(it.next())
	{
		Sprite *s = it.item();

		if(!s->draw())
			continue;

		if(s->animationBoundingBox().notIntersects(m_viewRect))
			continue;

		Vec drawPosition(s->position());

		if(!s->relative())
			drawPosition.sub(m_viewPos);

		m_pGraphics->drawSprite(s->currentFrame(), drawPosition, s->grabPoint(), s->trans(), s->tintColor(), s->opacity());
	}

	if(m_drawBounds)
		drawBounds();
}

void SpriteEngine::drawBounds()
{
	const static Color polyColor(0, 1, 0, 0.7);
	const static Color bboxColor(1, 0, 0, 0.7);
	const static Color animBboxColor(0, 0, 1, 0.7);

	SpriteContainer::Iterator it = m_sprites.iterator();

	while(it.next())
	{
		Sprite *s = it.item();

		if(!s->draw())
			continue;

		Rect drawRect(s->animationBoundingBox());

		if(!s->relative())
			drawRect.sub(m_viewPos);

		Polygon animBboxPoly(drawRect);
		m_pGraphics->drawPolygonOutline(&animBboxPoly, animBboxColor, Vec());

		if(!s->colliding())
			continue;

		BoundingShape *bs = s->boundingShape();

		Rect bbox(bs->boundingBox());
		bbox.transformLinear(s->trans());
		Polygon bboxPoly(bbox);

		Vec drawPos(s->position());

		if(!s->relative())
			drawPos.sub(m_viewPos);

		m_pGraphics->drawPolygonOutline(&bboxPoly, bboxColor, drawPos);

		if(bs->type() == BoundingShape::T_POLYGON)
		{
			BoundingPolygons *bps = dynamic_cast<BoundingPolygons*>(bs);

			int sz = bps->group()->polygonCount();

			for(int i = 0; i < sz; ++i)
			{
				m_pGraphics->drawPolygonOutline(bps->group()->polygon(i), polyColor, drawPos);
			}

		}
	}
}

void SpriteEngine::processCollisions()
{
	Rect bbA;
	Rect bbB;

	SpriteContainer::Iterator itA = m_sprites.iterator();

	while(itA.next())
	{
		Sprite *sA = itA.item();

		if(!sA->colliding())
			continue;

		BoundingShape *pBSA = sA->boundingShape();
		bbA.assign(pBSA->boundingBox());
		bbA.transform(sA->trans());

		SpriteContainer::Iterator itB(itA);

		while(itB.next())
		{
			Sprite *sB = itB.item();

			// relative sprites can collide only with
			// other relative sprites
			// the same with non relative
			if(!sB->colliding() || sA->relative() != sB->relative())
				continue;

			BoundingShape *pBSB = sB->boundingShape();
			bbB.assign(pBSB->boundingBox());
			bbB.transform(sB->trans());

			if(bbA.notIntersects(bbB))
				continue;

			if(pBSA->intersects(sA->trans(), pBSB, sB->trans()))
			{
				if(sA->onCollision(sB))
					sA->trans().restoreAll();

				if(sB->onCollision(sA))
					sB->trans().restoreAll();
			}
		}
	}
}

void SpriteEngine::setViewPos(const Vec &viewPos)
{
	m_viewPos.assign(viewPos);

	Vec br(viewPos);
	br.add(m_viewSize);

	m_viewRect.set(m_viewPos, br);
}
