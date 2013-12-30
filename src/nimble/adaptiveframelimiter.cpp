#include "adaptiveframelimiter.h"

#include "logger.h"

AdaptiveFrameLimiter::AdaptiveFrameLimiter(System *pSystem, float maxFps)
	: FrameLimiter(pSystem, maxFps)
{

}

void AdaptiveFrameLimiter::onInit()
{
	m_lastDelay = 0.0f;
}

void AdaptiveFrameLimiter::onFrame()
{
	float diff = (1.0f / m_maxFps) - m_lag;
	float delay = diff + 0.9f * m_lastDelay;

	m_lastDelay = delay;

	if(delay <= 0.0f)
	    return;

	m_pSystem->delay(static_cast<unsigned int>(delay * 1000.0f));
}

