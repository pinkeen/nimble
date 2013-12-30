#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>

class System
{
	private:
		std::string m_exePath;

		void readExecutablePath();

	public:
		System(int argc, char **argv);

		void localizePath(std::string &path);
		inline const std::string &exePath() const { return m_exePath; }

		unsigned int ticks();
		void delay(unsigned int ms);

		void init();
};

#endif // SYSTEM_H
