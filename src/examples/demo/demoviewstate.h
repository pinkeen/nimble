#ifndef DEMOVIEWSTATE_H
#define DEMOVIEWSTATE_H

#include <nimble/basicviewstate.h>

class DemoViewState : public BasicViewState
{
	private:
		KeyID m_escKeyID;

	public:
		DemoViewState(Configurator *pConfig);
		~DemoViewState();

		void onFrame(float lag);
		void onInit();

};

#endif // DEMOVIEWSTATE_H
