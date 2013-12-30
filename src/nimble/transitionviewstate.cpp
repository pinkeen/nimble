#include "transitionviewstate.h"

TransitionViewState::TransitionViewState(ViewState *pToState, float duration)
	: ViewState(pToState->config()), m_pToState(pToState), m_progress(0.0f), m_duration(duration)
{
	m_speed = 1.0f / m_duration;
}

void TransitionViewState::init()
{
	ViewState::init();
	input()->lock();
}

void TransitionViewState::frame(float lag)
{
	m_progress += lag * m_speed;

	onFrame(lag);

	if(m_progress >= 1.0f)
	{
		input()->unlock();
		changeState(m_pToState);
	}
}

void TransitionViewState::handlePreviousState(ViewState *pViewState)
{
	m_pFromState = pViewState;
}

TransitionViewState::~TransitionViewState()
{
	if(m_pFromState != 0)
		delete m_pFromState;
}
