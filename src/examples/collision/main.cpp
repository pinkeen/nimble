#include <nimble/nimble.h>

#include "mainviewstate.h"

int main(int argc, char **argv)
{
	System sys(argc, argv);
	Configurator conf(&sys);
	Application app(&conf);
	app.start(new MainViewState(&conf));

	INFO("Goodbye.");
}

