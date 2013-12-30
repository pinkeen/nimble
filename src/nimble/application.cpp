#include "application.h"

#include "logger.h"

Application::Application(Configurator *pConfig)
	: m_pConfig(pConfig)
{
	m_pFrameLimiter = m_pConfig->frameLimiter();
	m_pCurrentState = 0;
	m_pGraphics = m_pConfig->graphics();
	m_pSystem = m_pConfig->system();
	m_pInput = m_pConfig->input();
}

void Application::start(ViewState *pFirstState)
{
	m_pSystem->init();
	m_pGraphics->init();
	m_pCurrentState = pFirstState;
	m_pCurrentState->init();
	m_pFrameLimiter->init();

	bool quit = false;

	while(!quit)
	{
		m_pFrameLimiter->frame();

		float lag = m_pFrameLimiter->lag();

		m_pGraphics->clearBuffer();
		m_pInput->update();

		m_pCurrentState->frame(lag);

		m_pGraphics->swapBuffers();

		quit = m_pCurrentState->wantsQuit() || m_pInput->quit();

		ViewState *pNextState = m_pCurrentState->nextState();

		if(pNextState != 0)
		{
			pNextState->handlePreviousState(m_pCurrentState);
			m_pCurrentState = pNextState;
			m_pCurrentState->init();
		}
	}
}

Application::~Application()
{
	if(m_pCurrentState != 0)
		delete m_pCurrentState;
}
