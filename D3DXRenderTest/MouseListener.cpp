#include "MouseListener.h"

MouseListener::MouseListener( int priority )
	:Listener(ET_MOUSE, priority), 
	OnMouseDown(nullptr), OnMouseUp(nullptr), OnMouseMove(nullptr)
{
}

bool MouseListener::trigger( Event* event )
{
	switch(event->getParam())
	{
	case ET_MOUSE_DOWN:
		if(OnMouseDown)
			return OnMouseDown(event);
	case ET_MOUSE_UP:
		if(OnMouseUp)
			return OnMouseUp(event);
	case ET_MOUSE_MOVE:
		if(OnMouseMove)
			return OnMouseMove(event);
	default:
		break;
	}
	return false;
}
