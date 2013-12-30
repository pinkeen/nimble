#ifndef FLAMESPRITE_H
#define FLAMESPRITE_H

#include <nimble/sprite.h>

class FlameSprite : public Sprite
{
	private:
		Vec m_velocity;

		float m_growSpeed;
		float m_fadeSpeed;

	public:
		FlameSprite(SpriteEngine *pEngine, const Vec &position, const Vec &velocity);

		void onStep(float lag);
};

#endif // FLAMESPRITE_H
