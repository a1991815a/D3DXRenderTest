#ifndef __LAYER__
#define __LAYER__
#include "Node.h"

class Layer: public Node{
public:
	static Layer* create();
public:
	virtual void visit();
};
#endif