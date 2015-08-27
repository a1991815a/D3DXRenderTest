#include "Timer.h"
#include "TimerManager.h"

Timer::Timer()
	:m_time(0), m_pause(false)
{
	_timerManager->push(this);
}

Timer::~Timer()
{
	_timerManager->pop(this);
}

void Timer::setPause( bool pause )
{
	m_pause = pause;
}

bool Timer::getPause() const
{
	return m_pause;
}
