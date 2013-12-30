#ifndef TIMER_H
#define TIMER_H

#include <vector>

#include "timerobserver.h"

typedef int TimerID;

class Timer
{
	private:
		Timer(TimerID id, int shotLimit, float timeLimit, float interval);
		friend class TimerManager;

		std::vector<TimerObserver*> m_observers;
		typedef std::vector<TimerObserver*>::iterator ObserverPIterator;

		const TimerID m_id;
		const int m_shotLimit;
		const float m_timeLimit;
		const float m_interval;

		float m_elapsed;
		float m_nextShot;

		bool m_running;
		bool m_timeLimited;
		bool m_shotCountLimited;
		bool m_compensating;

		bool m_killed;

		int m_shotCount;
		int m_missedShotCount;

		inline void fire();
		void init();

	public:
		void step(float lag);
		inline void restart() { init(); }

		inline void pause() { m_running = false; }
		inline void resume() { m_running = true; }
		inline void kill() { m_killed = true; }

		inline void registerObserver(TimerObserver *pObserver)
			{ m_observers.push_back(pObserver); }

		inline bool killed() const { return m_killed; }
		inline bool running() const { return m_running; }
		inline float elapsed() const { return m_elapsed; }
		inline int shotCount() const { return m_shotCount; }
		inline int missedShotCount() const { return m_missedShotCount; }
		inline TimerID id() const { return m_id; }

		inline void disableCompensation() { m_compensating = false; }

		inline float delay() const { return m_elapsed - m_nextShot; }
};

#endif // TIMER_H
