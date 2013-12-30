#include "timermanager.h"

TimerID TimerManager::m_lastID = 0;

TimerManager::TimerManager()
{
}

TimerManager::~TimerManager()
{
	freeAll();
}

void TimerManager::freeAll()
{
	for(TimerPIterator it = m_timers.begin();
		it != m_timers.end(); ++it)
		delete *it;

	m_timers.clear();
}


void TimerManager::step(float lag)
{
	for(TimerPIterator it = m_timers.begin();
		it != m_timers.end(); ++it)
		(*it)->step(lag);

	commitKilled();
}

void TimerManager::commitKilled()
{
	TimerPIterator it = m_timers.begin();

	while(it != m_timers.end())
	{
		if((*it)->killed())
		{
			delete *it;
			TimerPIterator prev = it++;
			m_timers.erase(prev);
		}
		else ++it;
	}
}


Timer *TimerManager::createOneShot(TimerObserver *pObs, float time)
{
	Timer *pTimer = new Timer(generateID(), 1, 0.0f, time);
	pTimer->registerObserver(pObs);
	addTimer(pTimer);
	return pTimer;
}

Timer *TimerManager::createTimeLimited(TimerObserver *pObs, int shotCount, float time)
{
	Timer *pTimer = new Timer(generateID(), 0, time, time / (float)shotCount);
	pTimer->registerObserver(pObs);
	addTimer(pTimer);
	return pTimer;
}

Timer *TimerManager::createShotLimited(TimerObserver *pObs, float interval, float shots)
{
	Timer *pTimer = new Timer(generateID(), shots, 0.0f, interval);
	pTimer->registerObserver(pObs);
	addTimer(pTimer);
	return pTimer;
}

Timer *TimerManager::createShotLimitedFreq(TimerObserver *pObs, float frequency, float shots)
{
	Timer *pTimer = new Timer(generateID(), shots, 0.0f, 1.0f / frequency);
	pTimer->registerObserver(pObs);
	addTimer(pTimer);
	return pTimer;
}


Timer *TimerManager::createIndefinite(TimerObserver *pObs, float interval)
{
	Timer *pTimer = new Timer(generateID(), 0, 0.0f, interval);
	pTimer->registerObserver(pObs);
	addTimer(pTimer);
	return pTimer;
}

Timer *TimerManager::createIndefiniteFreq(TimerObserver *pObs, float frequency)
{
	Timer *pTimer = new Timer(generateID(), 0, 0.0f, 1.0f / frequency);
	pTimer->registerObserver(pObs);
	addTimer(pTimer);
	return pTimer;
}
