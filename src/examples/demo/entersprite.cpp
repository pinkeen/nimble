#include "entersprite.h"

#include <nimble/spriteengine.h>
#include <nimble/utils.h>

EnterSprite::EnterSprite(SpriteEngine *pEngine)
	: Sprite(pEngine, 2, 0, 0, Vec(), false, false, true, "EnterSprite")
{
	setAnimation(engine()->getAnimation("enter"));
	setGrabPointAtCenter();

	trans().position().set(engine()->viewRect().center().x(), 500);

	m_opdir = -1.0f;
	m_angdir = 1.0f;
}

void EnterSprite::onStep(float lag)
{
	const static float maxAngle = Utils::degToRad(10.0f);

	m_opacity += 2.0f * lag * m_opdir;

	if(m_opacity < 0.0f)
	{
		m_opacity = -m_opacity;
		m_opdir = 1.0f;
	}

	if(m_opacity > 1.0f)
	{
		m_opacity = 2.0f - m_opacity;
		m_opdir = -1.0f;
	}

	trans().rotateBy(maxAngle, lag * m_angdir);

	if(trans().angle() < -maxAngle)
	{
		trans().setAngle(-2.0f * maxAngle - trans().angle());
		m_angdir = 1.0f;
	}

	if(trans().angle() > maxAngle)
	{
		trans().setAngle(2.0f * maxAngle - trans().angle());
		m_angdir = -1.0f;
	}
}
