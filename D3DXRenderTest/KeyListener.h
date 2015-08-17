#ifndef __KEYLISTENER__
#define __KEYLISTENER__
#include "Listener.h"

class KeyListener: public Listener{
public:
	listenerFunc OnKeyDown;
	listenerFunc OnKeyUp;
public:
	KeyListener(int priority = 0);

	virtual bool trigger( Event* event );
};
#endif