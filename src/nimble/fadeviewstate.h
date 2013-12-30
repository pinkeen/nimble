#ifndef FADEVIEWSTATE_H
#define FADEVIEWSTATE_H

#include "transitionviewstate.h"

class FadeViewState : public TransitionViewState
{
	private:
		Color m_fadeColor;
		bool m_toInitialized;

	public:
		FadeViewState(ViewState *pToState, float duration, const Color &fadeColor);
		FadeViewState(ViewState *pToState, float duration);


		void onInit();
		void onFrame(float lag);
};

#endif // FADEVIEWSTATE_H
