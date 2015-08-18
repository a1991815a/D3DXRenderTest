#include "CustomListener.h"

CustomListener::CustomListener(EventTypes event_type, int priority /*= 0*/)
	:Listener(event_type, priority), EventCall(nullptr)
{

}

CustomListener::~CustomListener()
{

}

bool CustomListener::trigger(Event* event)
{
	return EventCall(event);
}
