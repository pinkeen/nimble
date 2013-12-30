#ifndef ENTERSPRITE_H
#define ENTERSPRITE_H

#include <nimble/sprite.h>

class EnterSprite : public Sprite
{
	private:
		float m_opdir;
		float m_angdir;
	public:
		EnterSprite(SpriteEngine *pEngine);

		void onStep(float lag);
};

#endif // ENTERSPRITE_H
