#include <nimble/nimble.h>

#include "mainviewstate.h"

int main(int argc, char **argv)
{
	System sys(argc, argv);
	Configurator conf(&sys);

	conf.setResolution(1280, 800);
	Application app(&conf);
	app.start(new MainViewState(&conf));

	INFO("Goodbye.");
}

