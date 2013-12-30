#include "timer.h"

Timer::Timer(TimerID id, int shotLimit, float timeLimit, float interval)
	: m_id(id), m_shotLimit(shotLimit), m_timeLimit(timeLimit), m_interval(interval)
{
	m_killed = false;
	m_compensating = true;

	init();

	m_shotCountLimited = true;

	if(m_shotLimit == 0)
		m_shotCountLimited = false;

	m_timeLimited = true;

	if(m_timeLimit == 0.0f)
		m_timeLimited = false;

}

void Timer::fire()
{
	for(ObserverPIterator it = m_observers.begin();
	    it != m_observers.end(); ++it)
		(*it)->onTimerFired(this);

	m_shotCount++;

	if(m_shotCountLimited && m_shotCount == m_shotLimit)
	{
		pause();
		kill();
	}
}

void Timer::init()
{
	m_shotCount = 0;
	m_running = true;
	m_elapsed = 0.0f;
	m_nextShot = m_interval;
	m_missedShotCount = 0;
}

void Timer::step(float lag)
{
	if(!m_running)
		return;

	m_elapsed += lag;

	if(m_elapsed >= m_nextShot)
	{
		float delay = m_elapsed - m_nextShot;
		int fireCount = 1;

		// oops, we missed some shots
		if(delay > m_interval)
			fireCount = static_cast<int>(delay / m_interval);

		// compensate for missed shots
		// useful when framerate is lower
		// than timer frequency
		if(m_compensating)
		{
			for(int i = 0; i < fireCount; ++i)
				fire();
		}
		else
		{
			m_missedShotCount = fireCount - 1;
			fire();
		}

		m_nextShot += fireCount * m_interval;
	}

	if(m_timeLimited && m_elapsed > m_timeLimit)
		kill();
}
