#ifndef __MOUSELISTENER__
#define __MOUSELISTENER__
#include "Listener.h"

class MouseListener: public Listener{
public:
	listenerFunc OnMouseDown;
	listenerFunc OnMouseUp;
	listenerFunc OnMouseMove;

public:
	MouseListener(int priority = 0);
	virtual bool trigger( Event* event );
};
#endif