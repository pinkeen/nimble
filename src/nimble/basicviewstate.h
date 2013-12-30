#ifndef BASICVIEWSTATE_H
#define BASICVIEWSTATE_H

#include "viewstate.h"
#include "timermanager.h"
#include "boundingshapemanager.h"

class BasicViewState : public ViewState
{
	protected:
		SpriteEngine *m_pSpriteEngine;
		AnimationManager *m_pAnimationHolder;
		ImageManager *m_pImageHolder;
		TimerManager *m_pTimerManager;
		BoundingShapeManager *m_pBoundingShapeManager;

		KeyID m_altKey;
		KeyID m_enterKey;

	public:
		BasicViewState(Configurator *pConfig);
		~BasicViewState();

		inline SpriteEngine *engine() const { return m_pSpriteEngine; }
		inline AnimationManager *anims() const { return m_pAnimationHolder; }
		inline ImageManager *images() const { return m_pImageHolder; }
		inline TimerManager *timers() const { return m_pTimerManager; }
		inline BoundingShapeManager *shapes() const { return m_pBoundingShapeManager; }

		void frame(float lag);

};

#endif // BASICVIEWSTATE_H
