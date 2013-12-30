#ifndef SPRITEENGINE_H
#define SPRITEENGINE_H

#include <vector>

#include "vector.h"
#include "graphics.h"
#include "configurator.h"
#include "spritecontainer.h"
#include "animationmanager.h"
#include "timermanager.h"
#include "input.h"
#include "boundingshapemanager.h"

class SpriteEngine
{
        private:
		Configurator *m_pConfig;
		Graphics *m_pGraphics;
		AnimationManager *m_pAnimManager;
		TimerManager *m_pTimerManager;
		BoundingShapeManager *m_pBoundingShapeManager;

		Input *m_pInput;

		Vec m_viewPos;
		Vec m_viewSize;
		Rect m_viewRect;

		SpriteContainer m_sprites;

		std::vector<Sprite*> m_spritesQueue;
		typedef std::vector<Sprite*>::iterator SpritePIterator;

		bool m_drawBounds;

		void processCollisions();
		void commitKilled();
		void updateSprites(float lag);
		void drawBounds();

        public:
		SpriteEngine(Configurator *pConfig, AnimationManager *pAnimManager, Input *pInput, TimerManager *pTimerManager, BoundingShapeManager *pBoundingShapeManager);
		~SpriteEngine();

                void registerSprite(Sprite *pSprite);
		void commitNewSprites();

		inline Animation* getAnimation(const std::string &name)
			{ return m_pAnimManager->animation(name); }

		inline BoundingShape* getBoundingShape(const std::string &name)
			{ return m_pBoundingShapeManager->shape(name); }

		inline const Rect &viewRect() const { return m_viewRect; }

		void toggleDrawingBounds() { m_drawBounds = !m_drawBounds; }

		void step(float lag);
		void draw();

		inline Input *input() const { return m_pInput; }
		inline TimerManager *timers() const { return m_pTimerManager; }

		void setViewPos(const Vec &viewPos);
		inline const Vec &viewPosition() const { return m_viewPos; }

		void centerOn(const Vec &point)
		{
			Vec tmp(point);
			Vec tmp2(m_viewSize);
			tmp2.div(2.0f);
			tmp.sub(tmp2);
			setViewPos(tmp);
		}
};

#endif // SPRITEENGINE_H
