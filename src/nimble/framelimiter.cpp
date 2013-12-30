#include "framelimiter.h"

FrameLimiter::FrameLimiter(System *pSystem, float maxFps)
	: m_pSystem(pSystem), m_maxFps(maxFps)
{

}

void FrameLimiter::init()
{
	m_ticks = m_oldTicks = m_pSystem->ticks();
	onInit();
}

void FrameLimiter::onInit() {}
void FrameLimiter::onFrame() {}

void FrameLimiter::frame()
{
	m_oldTicks = m_ticks;
	m_ticks = m_pSystem->ticks();

	m_lag = static_cast<float>(m_ticks - m_oldTicks) / 1000.0f;

	onFrame();
}

float FrameLimiter::fps()
{
	return 1.0f / m_lag;
}
