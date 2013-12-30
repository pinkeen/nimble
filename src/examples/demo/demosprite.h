#ifndef DEMOSPRITE_H
#define DEMOSPRITE_H

#include <nimble/sprite.h>
#include <nimble/timer.h>

class DemoSprite : public Sprite
{
	private:
		KeyID m_upKey;
		KeyID m_downKey;
		KeyID m_leftKey;
		KeyID m_rightKey;
		KeyID m_actionKey;

		Timer *m_pFTimer;

	public:
		DemoSprite(SpriteEngine *pEngine);

		void onTimerFired(Timer *pTimer);

		void onStep(float lag);
};

#endif // DEMOSPRITE_H
