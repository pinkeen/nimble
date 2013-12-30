#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <list>

#include "timer.h"

class TimerManager
{
	private:
		static TimerID m_lastID;
		static inline TimerID generateID() { return ++m_lastID; }

		std::list<Timer*> m_timers;
		typedef std::list<Timer*>::iterator TimerPIterator;

		void freeAll();
		inline void addTimer(Timer *pTimer) { m_timers.push_back(pTimer); }
		inline void commitKilled();

	public:
		TimerManager();
		~TimerManager();

		Timer *createOneShot(TimerObserver *pObs, float time);

		Timer *createTimeLimited(TimerObserver *pObs, int shotCount, float time);

		Timer *createShotLimited(TimerObserver *pObs, float interval, float shots);
		Timer *createShotLimitedFreq(TimerObserver *pObs, float frequency, float shots);

		Timer *createIndefinite(TimerObserver *pObs, float interval);
		Timer *createIndefiniteFreq(TimerObserver *pObs, float frequency);

		void step(float lag);
};

#endif // TIMERMANAGER_H
