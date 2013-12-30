#include "system.h"

#include "logger.h"
#include "utils.h"
#include <SDL/SDL.h>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


System::System(int argc, char **argv)
{
	Utils::initRandom();
	readExecutablePath();

	INFO("Executable path is: %s", m_exePath.c_str());
}

void System::init()
{
	ASSERT(SDL_Init(SDL_INIT_EVERYTHING) >= 0, "Could not init SDL: '%s'", SDL_GetError());

	atexit(SDL_Quit);
}

void System::readExecutablePath()
{
	char buf[1024];

	char delim;

#ifdef _WIN32
	GetModuleFileName(0, buf, 1024);
	delim = '\\';
#else
	ssize_t sz = readlink("/proc/self/exe", buf, 1024);
	buf[sz] = '\0';

	delim = '/';
#endif
	m_exePath.assign(buf);

	size_t pos = m_exePath.find_last_of(delim);
	m_exePath.erase(pos, m_exePath.length() - pos + 1);
}

void System::localizePath(std::string &path)
{
#ifdef _WIN32
	for(std::string::iterator ci = path.begin(); ci != path.end(); ++ci)
	{
		if(*ci == '/')
			*ci = '\\';
	}
#endif
}

unsigned int System::ticks()
{
	return SDL_GetTicks();
}

void System::delay(unsigned int ms)
{
	SDL_Delay(ms);
}
