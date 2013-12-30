#ifndef LOGOSPRITE_H
#define LOGOSPRITE_H

#include <nimble/sprite.h>

class LogoSprite : public Sprite
{
	private:
		Vec m_velocity;

	public:
		LogoSprite(SpriteEngine *pEngine);

		void onStep(float lag);
};

#endif // LOGOSPRITE_H
