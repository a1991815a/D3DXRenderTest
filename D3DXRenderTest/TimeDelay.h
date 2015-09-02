#ifndef __TIMEDELAY__
#define __TIMEDELAY__
#include "ActionInterval.h"

class TimeDelay: public ActionInterval{
public:
	static TimeDelay* create(long time);

private:
	virtual void _update();

private:
	long m_delay;
};
#endif