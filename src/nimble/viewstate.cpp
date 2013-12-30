#include "viewstate.h"
#include "logger.h"

ViewState::ViewState(Configurator *pConfig)
{
	m_pConfig = pConfig;
	m_pGraphics = m_pConfig->graphics();
	m_pInput = m_pConfig->input();
	m_initialized = false;
	m_quit = false;
	m_changed = false;
}

void ViewState::init()
{
	if(m_initialized)
		return;

	m_pNextState = 0;
	m_initialized = true;

	onInit();
}

void ViewState::changeState(ViewState *pState)
{
	ASSERT(!m_changed, "Double view state change - possible memory leaks!");

	// just to be safe
	input()->resetStates();

	m_changed = true;
	m_pNextState = pState;
}

void ViewState::frame(float lag)
{
	onFrame(lag);
}

void ViewState::quit()
{
	m_quit = true;
}

ViewState::~ViewState()
{
}

void ViewState::handlePreviousState(ViewState *pViewState)
{
	delete pViewState;
}
