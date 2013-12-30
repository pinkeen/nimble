#ifndef SPRITES_H
#define SPRITES_H

#include <nimble/nimble.h>

class ObstacleSprite : public Sprite
{
	public:
		ObstacleSprite(SpriteEngine *pEngine, Animation *pAnim, BoundingShape *pShape, const Vec &position, const Vec &grabPoint)
			: Sprite(pEngine, 0, pShape, pAnim, position, false, true, true, "Obstacle")
		{
			setGrabPoint(grabPoint);
			m_tintColor.set(1.0f, 0.0f, 0.0f, 0.0f);
		}

		void onStep(float lag)
		{
			m_tintColor.a() -= lag * 0.8f;

			if(m_tintColor.a() < 0.0f)
				m_tintColor.a() = 0.0f;
		}

		bool onCollision(Sprite *pOther)
		{
			m_tintColor.a() = 1.0f;

			return true;
		}
};

class PlayerSprite : public Sprite
{
	private:
		KeyID m_upKey;
		KeyID m_downKey;
		KeyID m_leftKey;
		KeyID m_rightKey;
		KeyID m_actionKey;

	public:
		PlayerSprite(SpriteEngine *pEngine, Animation *pAnim, BoundingShape *pShape, const Vec &position, const Vec &grabPoint)
			: Sprite(pEngine, 1, pShape, pAnim, position, false, true, true, "Player")
		{
			setGrabPoint(grabPoint);
			m_tintColor.set(1.0f, 0.0f, 0.0f, 0.0f);

			m_upKey = input()->keyID("up");
			m_downKey = input()->keyID("down");
			m_leftKey = input()->keyID("left");
			m_rightKey = input()->keyID("right");
			m_actionKey = input()->keyID("space");
		}

		void onStep(float lag)
		{
			m_tintColor.a() -= lag * 0.8f;

			if(m_tintColor.a() < 0.0f)
				m_tintColor.a() = 0.0f;

			static const float speed = 200.0f;

			if(input()->keyState(m_upKey))
				position().y() -= speed * lag;

			if(input()->keyState(m_leftKey))
				position().x() -= speed * lag;

			if(input()->keyState(m_rightKey))
				position().x() += speed * lag;

			if(input()->keyState(m_downKey))
				position().y() += speed * lag;

			if(input()->keyState(m_actionKey))
				trans().rotateByDeg(10.0f, lag);
		}

		bool onCollision(Sprite *pOther)
		{
			m_tintColor.a() = 1.0f;
			return true;
		}

};

#endif // SPRITES_H
