#include "fadeviewstate.h"

FadeViewState::FadeViewState(ViewState *pToState, float duration, const Color &fadeColor)
	: TransitionViewState(pToState, duration), m_fadeColor(fadeColor)
{
	m_toInitialized = false;
}

FadeViewState::FadeViewState(ViewState *pToState, float duration)
	: TransitionViewState(pToState, duration)
{
	m_toInitialized = false;
}

void FadeViewState::onInit()
{

}

void FadeViewState::onFrame(float lag)
{
	if(m_progress <= 0.5f)
	{
		m_pFromState->frame(lag);
		m_fadeColor.a() = m_progress / 0.5f;
	}
	else
	{
		if(!m_toInitialized)
		{
			m_toInitialized = true;
			delete m_pFromState;
			m_pFromState = 0;
			m_pToState->init();
		}

		m_pToState->frame(lag);
		m_fadeColor.a() = 1.0f - ((m_progress - 0.5f) / 0.5f);
	}

	m_pGraphics->fillScreen(m_fadeColor);
}
