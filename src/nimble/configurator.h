/**
 * \file configurator.h
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "vector.h"
#include "graphics.h"
#include "system.h"
#include "framelimiter.h"
#include "input.h"

#include <string>

class Graphics;

class Configurator
{
	private:
		Graphics *m_pGraphics;
		System *m_pSystem;
		FrameLimiter *m_pFrameLimiter;
		Input *m_pInput;

		int m_resX;
		int m_resY;

		float m_maxFps;

		std::string m_dataPath;

		std::string m_frameLimiterName;
		std::string m_graphicsName;

		bool m_dataPathRelative;
		bool m_startFullscreen;

		void createFrameLimiter(const std::string &name);
		void createGraphics(const std::string &name);

	public:
		Configurator(System *pSystem);
		~Configurator();

		void readConfig();
		void saveConfig();

		inline int screenWidth() const { return m_resX; }
		inline int screenHeight() const { return m_resY; }

		inline const std::string &frameLimiterName() { return m_frameLimiterName; }
		inline const std::string &graphicsName() { return m_graphicsName; }
		inline bool fullscreen() { return m_startFullscreen; }

		inline void setFrameLimiter(const std::string &name) { m_frameLimiterName.assign(name); }
		inline void setGraphicsName(const std::string &name) { m_graphicsName.assign(name); }
		inline void setResolution(int X, int Y) { m_resX = X; m_resY = Y; }
		inline void setStartFullscreen(bool v) { m_startFullscreen = v; }

		Graphics *graphics();
		FrameLimiter *frameLimiter();

		Input *input();
		System *system();

		std::string resourcePath(const std::string &path);
};

#endif // CONFIGURATOR_H
