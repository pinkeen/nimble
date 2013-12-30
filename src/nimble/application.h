#ifndef APPLICATION_H
#define APPLICATION_H

#include "viewstate.h"
#include "framelimiter.h"
#include "configurator.h"
#include "graphics.h"
#include "input.h"
#include "system.h"

class Application
{
	private:
		ViewState *m_pCurrentState;
		Configurator *m_pConfig;
		FrameLimiter *m_pFrameLimiter;
		Graphics *m_pGraphics;
		System *m_pSystem;
		Input *m_pInput;

	public:
		Application(Configurator *pConfig);
		~Application();

		void start(ViewState *pFirstState);
};

#endif // APPLICATION_H
