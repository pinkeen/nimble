/**
 * \file graphics.cpp
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#include "graphics.h"

#include "logger.h"

Graphics::Graphics(Configurator *pConfigurator)
{
	m_pConfigurator = pConfigurator;
}

void Graphics::init()
{
	m_resX = m_pConfigurator->screenWidth();
	m_resY = m_pConfigurator->screenHeight();
	m_fullscreen = m_pConfigurator->fullscreen();

	onInit();
}
