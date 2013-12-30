#ifndef TIMEROBSERVER_H
#define TIMEROBSERVER_H

class Timer;

class TimerObserver
{
	public:
		virtual void onTimerFired(Timer *pTimer) {}
};

#endif // TIMEROBSERVER_H
