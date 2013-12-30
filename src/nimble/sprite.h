#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>
#include <map>

#include "animation.h"
#include "vector.h"
#include "sprite.h"
#include "color.h"
#include "timerobserver.h"
#include "timermanager.h"
#include "input.h"
#include "boundingshape.h"
#include "utils.h"
#include "transformation.h"

class SpriteEngine;

class Sprite : public TimerObserver
{
        private:
                Vec m_grabPoint;

                const std::string m_name;
                const int m_layer;
                bool m_relative;
		bool m_colliding;
		bool m_draw;
		bool m_killed;

		SpriteEngine *m_pEngine;
		BoundingShape *m_pBoundingShape;
		Animation *m_pAnimation;
		Animation *m_pNextAnimation;
		TimerManager *m_pTimerManager;
		Input *m_pInput;

		typedef struct
		{
			Vec *pBaseVec;
			Vec *pTransVec;
		} ActionPoint;

		std::map<std::string, ActionPoint> m_actionPoints;
		typedef std::map<std::string, ActionPoint>::iterator ActionPointIterator;

		void updateActionPoints();
		void deleteActionPoints();

        protected:
		Transformation m_trans;

		float m_opacity;
                Color m_tintColor;

                float m_frame;
                float m_animDir;

		bool m_animate;

                Vec m_drawPosition;
		Rect m_boundBox;

		virtual void initDefaults();
		const Vec *getActionPoint(const std::string &name);

	public:
		Sprite(SpriteEngine *pEngine, int layer, BoundingShape *pShape, Animation *pAnim,
		       const Vec &position, bool relative, bool colliding, bool draw, const std::string &name);

		virtual ~Sprite();

                inline int layer() const { return m_layer; }
                inline const Vec& grabPoint() const { return m_grabPoint; }
                inline float opacity() const { return m_opacity; }
		inline const std::string &name() const { return m_name; }
                inline const Color &tintColor() const { return m_tintColor; }
		inline Transformation &trans() { return m_trans; }
		inline Vec &position() { return m_trans.position(); }

		inline bool relative() const { return m_relative; }
		inline bool colliding() const { return m_colliding; }
		inline bool killed() const { return m_killed; }
		inline bool draw() const { return m_draw; }

		inline Animation *animation() const { return m_pAnimation; }
		inline Input *input() const { return m_pInput; }
		inline SpriteEngine *engine() const { return m_pEngine; }
		inline TimerManager *timers() const { return m_pTimerManager; }

		inline void setGrabPoint(const Vec &grabPoint) { m_grabPoint = grabPoint; }
		inline void setGrabPointAtCenter() { m_grabPoint.assign(m_pAnimation->boundingBox().center()); }

		void relativize();

		inline void kill() { m_killed = true; }

		virtual void onUpdateAnimation(float lag, bool finished);
		virtual bool onCollision(Sprite *pOther);

		inline BoundingShape *boundingShape() const { return m_pBoundingShape; }

                inline AnimationFrame *currentFrame() const
			{ return m_pAnimation->getFrame((int)m_frame); }

		void updateAnimation(float lag);

		inline void step(float lag)
		{
			m_trans.storeOld();
			updateActionPoints();
			onStep(lag);
		}

		virtual void onStep(float lag);

		inline const Rect &animationBoundingBox()
		{
			m_boundBox.assign(m_pAnimation->boundingBox());
			m_boundBox.sub(m_grabPoint);

			m_boundBox.transform(m_trans);

			return m_boundBox;
		}

		inline void setAnimation(Animation *pAnimation)
		{
			m_pNextAnimation = m_pAnimation = pAnimation;
			m_frame = 0.0f;
			m_animDir = 1.0f;
		}

		inline void switchAnimation(Animation *pAnimation) { m_pNextAnimation = pAnimation; }

		inline void setBoundingShape(BoundingShape *pBoundingShape) { m_pBoundingShape = pBoundingShape; }

		const Vec *addActionPoint(const std::string &name, const Vec &point);
};

#endif // SPRITE_H
