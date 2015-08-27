#ifndef __ACTIONINTERVAL__
#define __ACTIONINTERVAL__
#include "Action.h"
#include "Timer.h"

class ActionInterval: public Action{
public:
	void setDelay(time_type delay);
	time_type getDelay() const;
	virtual void update() override;

	void setPause(bool pause);
	bool getPause() const;
	time_type getDelta() const;
private:
	Timer m_timer;
	time_type m_delay;
};
#endif