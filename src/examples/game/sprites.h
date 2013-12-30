#ifndef SPRITES_H
#define SPRITES_H

#include <nimble/nimble.h>

class MonsterSprite : public Sprite
{
	private:
		float m_health;
		float m_speed;
		float m_killed;

		Animation *m_pBurnAnim;

	public:
		MonsterSprite(SpriteEngine *pEngine, const Vec &position)
			: Sprite(pEngine, 0, 0, 0, position, false, true, true, "Monster")
		{
			setAnimation(engine()->getAnimation("Monster"));
			setBoundingShape(engine()->getBoundingShape("Monster"));

			setGrabPointAtCenter();

			m_pBurnAnim = engine()->getAnimation("MonsterBurn");

			m_health = 1.0f;
			m_speed = Utils::randFloat(50.0f, 100.0f);
			m_opacity = 0.0f;
			m_killed = false;
		}

		void onStep(float lag)
		{
			if(m_killed)
			{
				m_opacity -= lag / 10.0f;

				if(m_opacity <= 0.0f)
				{
					m_opacity = 0.0f;
					kill();
				}

				return;
			}

			m_opacity += lag * 1.0f;

			if(m_opacity > 1.0f)
				m_opacity = 1.0f;

			if(m_health <= 0.0f)
			{
				m_killed = true;
				switchAnimation(m_pBurnAnim);
			}

			trans().moveBy(Utils::angleVector(trans().angle(), m_speed * m_health), lag);
		}

		bool onCollision(Sprite *pOther)
		{
			if(m_killed)
				return false;

			if(pOther->name() == "Flame")
			{
				m_health -= 0.05;
				return false;
			}

			trans().restorePosition();
			trans().restoreScale();
			trans().rotateBy((float)Utils::randInt(1, 2) * 3.14f / 2.0f);

			return false;
		}
};

class ContainerSprite : public Sprite
{
	public:
		ContainerSprite(SpriteEngine *pEngine, const Vec &position)
			: Sprite(pEngine, 0, 0, 0, position, false, true, true, "Container")
		{
			setAnimation(engine()->getAnimation("Container"));
			setBoundingShape(engine()->getBoundingShape("Container"));
			setGrabPointAtCenter();
		}

		bool onCollision(Sprite *pOther)
		{
			return false;
		}

};

class FlameSprite : public Sprite
{
	private:
		Vec m_velocity;

		float m_growSpeed;
		float m_fadeSpeed;
		float m_rotSpeed;

	public:
		FlameSprite(SpriteEngine *pEngine, const Vec &position, const Vec &velocity)
			: Sprite(pEngine, 0, 0, 0, position, false, true, true, "Flame"),
			m_velocity(velocity)
		{
			setBoundingShape(engine()->getBoundingShape("Flame"));
			setAnimation(pEngine->getAnimation("Flame"));
			setGrabPointAtCenter();

			trans().setScale(0.1f, 0.1f);
			m_velocity.add(Utils::randFloat(-10.0f, 10.0f), Utils::randFloat(-10.0f, 10.0f));
			m_growSpeed = Utils::randFloat(1.0f, 1.5f);
			//m_fadeSpeed = Utils::randFloat(1.0f, 1.5f);
			m_fadeSpeed = 1.0f;
			m_rotSpeed = Utils::randFloat(-6.0f, 6.0f);
		}

		void onStep(float lag)
		{
			trans().moveBy(m_velocity, lag);

			m_opacity -= m_fadeSpeed * lag;

			trans().addScale(m_growSpeed, lag);
			trans().rotateBy(m_rotSpeed, lag);

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

		bool onCollision(Sprite *pOther)
		{
			if(pOther->name() == "Monster")
				kill();

			return false;
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

		Animation *m_standA;
		Animation *m_walkA;
		Animation *m_shootA;

		Timer *m_pFlameTimer;

		const Vec *m_pGunPoint;


	public:
		PlayerSprite(SpriteEngine *pEngine, const Vec &position)
			: Sprite(pEngine, 1, 0, 0, position, false, true, true, "Player")
		{
			m_upKey = input()->keyID("up");
			m_downKey = input()->keyID("down");
			m_leftKey = input()->keyID("left");
			m_rightKey = input()->keyID("right");
			m_actionKey = input()->keyID("space");

			m_standA = engine()->getAnimation("Player");
			m_walkA = engine()->getAnimation("PlayerWalk");
			m_shootA = engine()->getAnimation("PlayerShoot");

			setBoundingShape(engine()->getBoundingShape("Player"));
			setAnimation(m_standA);

			setGrabPointAtCenter();

			m_pFlameTimer = timers()->createIndefiniteFreq(this, 30.0f);
			m_pFlameTimer->pause();

			Vec tmp(0.0f, 13.0f);
			tmp.sub(grabPoint());
			m_pGunPoint = addActionPoint("gunPoint", tmp);
			//m_pGunPoint = getActionPoint("gunPoint");
		}

		void onStep(float lag)
		{
			static const float speed = 200.0f;
			static const float rotspeed = 6.0f;

			switchAnimation(m_standA);

			if(input()->keyState(m_leftKey))
			{
				trans().rotateBy(-rotspeed, lag);
				switchAnimation(m_walkA);
			}

			if(input()->keyState(m_rightKey))
			{
				trans().rotateBy(rotspeed, lag);
				switchAnimation(m_walkA);
			}

			if(input()->keyState(m_actionKey))
			{
				m_pFlameTimer->resume();
				switchAnimation(m_shootA);
				return;
			}
			else
			{
				m_pFlameTimer->pause();
			}

			if(input()->keyState(m_upKey))
			{
				trans().moveBy(Utils::angleVector(trans().angle(), -speed), lag);
				switchAnimation(m_walkA);
			}

			if(input()->keyState(m_downKey))
			{
				trans().moveBy(Utils::angleVector(trans().angle(), speed), lag);
				switchAnimation(m_walkA);
			}

			engine()->centerOn(position());
		}

		bool onCollision(Sprite *pOther)
		{
			if(pOther->name() == "Monster")
				return true;

			if(pOther->name() == "Container")
				return true;

			return false;
		}

		void onTimerFired(Timer *pTimer)
		{
			if(pTimer->id() == m_pFlameTimer->id())
			{
				new FlameSprite(engine(), *m_pGunPoint, Utils::angleVector(trans().angle(), -Utils::randFloat(100.0f, 200.0f)));
			}
		}
};

#endif // SPRITES_H
