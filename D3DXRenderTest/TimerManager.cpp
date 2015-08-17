#include "TimerManager.h"
#include <windows.h>
#include "GBAssert.h"


TimerManager::TimerManager()
{
	m_timerList.reserve(100);
}

TimerManager::~TimerManager()
{

}

bool TimerManager::init()
{
	m_curTime = m_preTime = m_startTime = GetTickCount64();
	return true;
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

void TimerManager::push(Timer* _timer)
{
	GBASSERT(m_timerList.find(_timer) == m_timerList.end());
	m_timerList.insert(_timer);
}

void TimerManager::pop(Timer* _timer)
{
	GBASSERT(m_timerList.find(_timer) != m_timerList.end());
	m_timerList.erase(_timer);
}
