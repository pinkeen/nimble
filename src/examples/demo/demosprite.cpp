#include "demosprite.h"

#include <nimble/spriteengine.h>
#include <nimble/utils.h>

#include "flamesprite.h"

DemoSprite::DemoSprite(SpriteEngine *pEngine)
	: Sprite(pEngine, 2, 0, 0, Vec(200, 200), false, false, true, "DemoSprite")
{
	setAnimation(pEngine->getAnimation("demoAnim"));
	setGrabPointAtCenter();
	trans().position().assign(engine()->viewRect().center());

	m_upKey = input()->keyID("up");
	m_downKey = input()->keyID("down");
	m_leftKey = input()->keyID("left");
	m_rightKey = input()->keyID("right");
	m_actionKey = input()->keyID("space");

	m_pFTimer = timers()->createIndefiniteFreq(this, 100.0f);
	m_pFTimer->pause();

}


void DemoSprite::onStep(float lag)
{
	static const float speed = 200.0f;

	trans().rotateByDeg(180.0f, lag);

	if(input()->keyState(m_upKey))
		trans().position().y() -= speed * lag;

	if(input()->keyState(m_leftKey))
		trans().position().x() -= speed * lag;

	if(input()->keyState(m_rightKey))
		trans().position().x() += speed * lag;

	if(input()->keyState(m_downKey))
		trans().position().y() += speed * lag;

	if(input()->keyState(m_actionKey))
		m_pFTimer->resume();
	else
		m_pFTimer->pause();

}

void DemoSprite::onTimerFired(Timer *pTimer)
{
	if(pTimer->id() == m_pFTimer->id())
	{
		new FlameSprite(engine(), position(), Utils::angleVector(Utils::degToRad(Utils::randFloat(-130.0f, -50.0f)), Utils::randFloat(150.0f, 300.0f)));
	}
}
