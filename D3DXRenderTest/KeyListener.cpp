#include "KeyListener.h"

KeyListener::KeyListener( int priority)
	:Listener(ET_KEY, priority), OnKeyDown(nullptr), OnKeyUp(nullptr)
{}

bool KeyListener::trigger( Event* event )
{
	switch(event->getParam()){
	case ET_KEY_DOWN:
		if(OnKeyDown)
			return OnKeyDown(event);
	case ET_KEY_UP:
		if(OnKeyUp)
			return OnKeyUp(event);
	default:
		break;
	}
	return false;
}
