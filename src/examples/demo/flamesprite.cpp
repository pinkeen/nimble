#include "flamesprite.h"

#include <nimble/spriteengine.h>
#include <nimble/utils.h>
#include <nimble/logger.h>

FlameSprite::FlameSprite(SpriteEngine *pEngine, const Vec &position, const Vec &velocity)
	: Sprite(pEngine, 0, 0, 0, position, false, false, true, "FlameSprite"),
	m_velocity(velocity)
{
	setAnimation(pEngine->getAnimation("particle"));
	setGrabPointAtCenter();
	m_growSpeed = Utils::randFloat(-1.0f, 1.0f);
	m_fadeSpeed = Utils::randFloat(0.2f, 2.0f);

	m_tintColor.set(Utils::randFloat(), Utils::randFloat(), Utils::randFloat(), 0.7);

}

void FlameSprite::onStep(float lag)
{
	trans().moveBy(m_velocity, lag);

	m_opacity -= m_fadeSpeed * lag;

	trans().addScale(m_growSpeed, lag);

	// gravity sim
	m_velocity.y() += 100.0f * lag;

	if(trans().scale().x() <= 0.0f)
	{
		trans().setScale(0.0f, 0.0f);
		kill();
	}

	if(m_opacity <= 0.0f)
	{
		m_opacity = 0.0f;
		kill();
	}
}
