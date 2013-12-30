#ifndef VIEWSTATE_H
#define VIEWSTATE_H

#include "imagemanager.h"
#include "animationmanager.h"
#include "spriteengine.h"
#include "graphics.h"
#include "configurator.h"
#include "input.h"
#include "timerobserver.h"

class ViewState : public TimerObserver
{
	private:
		bool m_quit;
		bool m_initialized;
		bool m_changed;

		ViewState *m_pNextState;

	protected:
		Configurator *m_pConfig;
		Graphics *m_pGraphics;
		Input *m_pInput;

		void changeState(ViewState *pState);

	public:
		ViewState(Configurator *pConfig);

		virtual void init();
		virtual void onInit() = 0;
		virtual void frame(float lag);
		virtual void onFrame(float lag) = 0;

		inline Configurator *config() const { return m_pConfig; };
		inline Input *input() const { return m_pInput; };
		inline Graphics *graphics() const { return m_pGraphics; };

		void quit();

		inline bool wantsQuit() const { return m_quit; }
		ViewState *nextState() const { return m_pNextState; }

		virtual void handlePreviousState(ViewState *pViewState);
		virtual ~ViewState();
};

#endif // VIEWSTATE_H
