#include "logosprite.h"

#include <nimble/spriteengine.h>
#include <nimble/logger.h>

LogoSprite::LogoSprite(SpriteEngine *pEngine)
	: Sprite(pEngine, 0, 0, 0, Vec(200, 100), false, false, true, "LogoSprite")
{
	setAnimation(engine()->getAnimation("logo"));
	setGrabPointAtCenter();
	trans().position().set(engine()->viewRect().center().x(), 50.0f);
}

void LogoSprite::onStep(float lag)
{

	m_velocity.add(0.0f, 400.0f * lag);

	if(m_velocity.length() < 1.0f)
		return;

	trans().moveBy(m_velocity, lag);

	if(position().y() > 300.0f)
	{
		position().y() = 600.0f - position().y();
		m_velocity.y() = -m_velocity.y() * 0.6f;
	}

}
