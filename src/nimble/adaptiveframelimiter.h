#ifndef ADAPTIVEFRAMELIMITER_H
#define ADAPTIVEFRAMELIMITER_H

#include "framelimiter.h"

class AdaptiveFrameLimiter : public FrameLimiter
{
	private:
		float m_lastDelay;

	public:
		AdaptiveFrameLimiter(System *pSystem, float maxFps);

		void onInit();
		void onFrame();


};

#endif // ADAPTIVEFRAMELIMITER_H
