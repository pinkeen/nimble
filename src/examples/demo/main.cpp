/**
 * \file main.cpp
 * \author Filip Sobalski <pinkeen@gmail.com>
 */

#include <nimble/nimble.h>
#include "splashviewstate.h"

int main(int argc, char **argv)
{
	System sys(argc, argv);
	Configurator conf(&sys);

	conf.setResolution(1280, 800);
	conf.setFrameLimiter("Max");
	conf.setGraphicsName("OpenGL");
	conf.setStartFullscreen(false);

	Application app(&conf);
	app.start(new SplashViewState(&conf));

	INFO("Goodbye.");
}

