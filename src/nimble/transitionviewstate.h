#ifndef TRANSITIONVIEWSTATE_H
#define TRANSITIONVIEWSTATE_H

#include "viewstate.h"

class TransitionViewState : public ViewState
{
	protected:
		ViewState *m_pFromState;
		ViewState *m_pToState;

		float m_progress;
		float m_duration;
		float m_speed;

	public:
		TransitionViewState(ViewState *pToState, float duration);
		~TransitionViewState();

		void init();
		void frame(float lag);
		void handlePreviousState(ViewState *pViewState);
};

#endif // TRANSITIONVIEWSTATE_H
