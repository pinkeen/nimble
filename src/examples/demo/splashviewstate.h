#ifndef SPLASHVIEWSTATE_H
#define SPLASHVIEWSTATE_H

#include <nimble/basicviewstate.h>

class SplashViewState : public BasicViewState
{
	private:
		KeyID m_enterKeyID;

	public:
		SplashViewState(Configurator *pConfig);
		~SplashViewState();

		void onFrame(float lag);
		void onInit();
};

#endif // SPLASHVIEWSTATE_H
