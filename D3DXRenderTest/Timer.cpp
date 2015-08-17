#include "Timer.h"
#include "TimerManager.h"

Timer::Timer()
	:m_time(0)
{
	_timerManager->push(this);
}

Timer::~Timer()
{
	_timerManager->pop(this);
}
