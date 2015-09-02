#include "TimeDelay.h"

TimeDelay* TimeDelay::create(long time)
{
	TimeDelay* ret = nullptr;
	gbAlloc(ret);
	ret->autorelease();
	ret->m_delay = time;
	return ret;
}

void TimeDelay::_update()
{
	if((m_delay -= getDelta()) <= 0)
		setStop(true);
}
