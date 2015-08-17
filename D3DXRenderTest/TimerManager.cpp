#include "TimerManager.h"
#include <windows.h>

bool TimerManager::init()
{
	m_curTime = m_preTime = m_startTime = GetTickCount64();
}

void TimerManager::loop()
{
	m_curTime = GetTickCount64();
	time_type delta = m_curTime - m_preTime;
	m_preTime = m_curTime;
	auto itor = m_timerList.begin();
	for (; itor != m_timerList.end(); ++itor)
	{
		Timer* timer = *itor;
		timer->m_time += delta;
	}
}

void TimerManager::destroy()
{
	
}
