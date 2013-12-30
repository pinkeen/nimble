#include "sprite.h"

#include <cmath>

#include "spriteengine.h"

Sprite::Sprite(SpriteEngine *pEngine, int layer, BoundingShape *pShape, Animation *pAnim,
       const Vec &position, bool relative, bool colliding, bool draw, const std::string &name)
	: m_name(name), m_layer(layer), m_relative(relative), m_colliding(colliding),
	m_draw(draw), m_pEngine(pEngine), m_pBoundingShape(pShape), m_pAnimation(pAnim), m_pNextAnimation(pAnim), m_trans(position)
{
	initDefaults();
	m_pEngine->registerSprite(this);
	m_pInput = m_pEngine->input();
	m_pTimerManager = m_pEngine->timers();
}

void Sprite::initDefaults()
{
	m_grabPoint.set(0.0f, 0.0f);
	m_opacity = 1.0f;
	m_frame = 0.0f;
	m_animDir = 0.0f;
	m_animate = true;
	m_killed = false;
}

Sprite::~Sprite()
{
	deleteActionPoints();
}

void Sprite::onUpdateAnimation(float lag, bool finished)
{
}

void Sprite::updateAnimation(float lag)
{
	if(!m_animate)
		return;

	if(m_pAnimation == 0)
		return;

	if(m_pNextAnimation != m_pAnimation)
	{
		m_pAnimation = m_pNextAnimation;
		m_frame = 0.0f;
		m_animDir = 1.0f;
	}

	if(m_animDir == 0.0f)
		onUpdateAnimation(lag, true);

	float frameCount = (float)m_pAnimation->frameCount();
	float delta = m_pAnimation->fps() * lag;

	if(delta >= 1.0f)
		delta -= truncf(delta);

	m_frame += delta * m_animDir;

	if(m_frame >= frameCount)
	{
		if(m_pAnimation->reverse())
		{
			m_frame -= frameCount - (m_frame - frameCount);
			m_animDir = -1.0f;
		}
		else
		{
			m_frame = m_frame - frameCount;
			onUpdateAnimation(lag, true);

			if(!m_pAnimation->loop())
			{
				m_animDir = 0.0f;
				m_frame = frameCount - 1.0f;
			}
		}
	}

	if(m_frame < 0.0f)
	{
		m_frame = -m_frame;
		m_animDir = 1.0f;
		onUpdateAnimation(lag, true);

		if(!m_pAnimation->loop())
		{
			m_animDir = 0.0f;
			m_frame = 0.0f;
		}
	}

	onUpdateAnimation(lag, false);
}

void Sprite::relativize()
{
	if(m_relative)
		return;

	m_trans.position().sub(m_pEngine->viewPosition());
	m_relative = true;
}

void Sprite::onStep(float lag)
{
}

bool Sprite::onCollision(Sprite *pOther) { return false; }


void Sprite::deleteActionPoints()
{
	ActionPointIterator it = m_actionPoints.begin();

	while(it != m_actionPoints.end())
	{
		delete it->second.pBaseVec;
		delete it->second.pTransVec;
		++it;
	}

	m_actionPoints.clear();
}

const Vec *Sprite::getActionPoint(const std::string &name)
{
	ActionPointIterator it = m_actionPoints.find(name);
	ASSERT(it != m_actionPoints.end(), "Could not find action point '%s'!", name.c_str());

	return it->second.pTransVec;
}

const Vec *Sprite::addActionPoint(const std::string &name, const Vec &point)
{
	ActionPoint ap = {new Vec(point), new Vec(point)};
	m_actionPoints[name] = ap;
	return ap.pTransVec;
}

void Sprite::updateActionPoints()
{
	ActionPointIterator it = m_actionPoints.begin();

	while(it != m_actionPoints.end())
	{
		it->second.pTransVec->assign(*(it->second.pBaseVec));
		m_trans.transform(*(it->second.pTransVec));
		++it;
	}
}

