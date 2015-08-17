#ifndef __CUSTOMLISTENER__
#define __CUSTOMLISTENER__
#include "Listener.h"

class CustomListener: public Listener{
public:
	listenerFunc EventCall;										//事件回调函数

public:
	CustomListener(EventTypes event_type, int priority = 0);
	~CustomListener();

	virtual bool trigger(Event* event) override;
};
#endif