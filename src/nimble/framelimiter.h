#ifndef FRAMELIMITER_H
#define FRAMELIMITER_H

#include "system.h"

class FrameLimiter
{
	protected:
		System *m_pSystem;

		unsigned int m_oldTicks;
		unsigned int m_ticks;

		float m_lag;
		float m_maxFps;

		virtual void onInit();
		virtual void onFrame();

	public:
		FrameLimiter(System *pSystem, float maxFps);

		void init();
		void frame();
		float fps();

		inline float lag() const { return m_lag; }
};

#endif // FRAMELIMITER_H
