/**
 * \file configurator.cpp
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#include "configurator.h"
#include "adaptiveframelimiter.h"
#include "opengl/oglgraphics.h"
#include "logger.h"

void Configurator::readConfig()
{
}

void Configurator::saveConfig()
{
}

std::string Configurator::resourcePath(const std::string &path)
{
	std::string fullPath;
	std::string resPath(m_dataPath);

	if(path[0] != '/')
		resPath.append("/");

	resPath.append(path);


	if(m_dataPathRelative)
		fullPath = m_pSystem->exePath();

	m_pSystem->localizePath(resPath);

	fullPath.append(resPath);
	return fullPath;
}

Configurator::Configurator(System *pSystem)
	: m_pSystem(pSystem), m_frameLimiterName("Default"), m_graphicsName("Default")
{
	m_resX = 800;
	m_resY = 600;
	m_pGraphics = 0;
	m_pFrameLimiter = 0;

	m_startFullscreen = 0;

	m_pInput = new Input();

	m_dataPath = "/data";
	m_dataPathRelative = true;

}

Graphics *Configurator::graphics()
{
	if(m_pGraphics == 0)
		createGraphics(m_graphicsName);

	return m_pGraphics;
}

FrameLimiter *Configurator::frameLimiter()
{
	if(m_pFrameLimiter == 0)
		createFrameLimiter(m_frameLimiterName);

	return m_pFrameLimiter;
}

Input *Configurator::input()
{
	return m_pInput;
}

System *Configurator::system()
{
	return m_pSystem;
}

Configurator::~Configurator()
{
	if(m_pGraphics != 0)
		delete m_pGraphics;

	if(m_pFrameLimiter != 0)
		delete m_pFrameLimiter;

	if(m_pInput != 0)
		delete m_pInput;
}

void Configurator::createFrameLimiter(const std::string &name)
{
	INFO("Initializing '%s' FrameLimiter...", name.c_str());

	if(name == "Max")
	{
		m_pFrameLimiter = new FrameLimiter(m_pSystem, m_maxFps);
		return;
	}

	if(name == "Adaptive" || name == "Default")
	{
		m_pFrameLimiter = new AdaptiveFrameLimiter(m_pSystem, m_maxFps);
		return;
	}

	ERROR("FrameLimiter '%s' is not available!", name.c_str());
}

void Configurator::createGraphics(const std::string &name)
{
	INFO("Initializing '%s' Graphics...", name.c_str());

	if(name == "OpenGL" || name == "Default")
	{
		m_pGraphics = new OGLGraphics(this);
		return;
	}

	ERROR("Graphics backend '%s' is not available!", name.c_str());
}
