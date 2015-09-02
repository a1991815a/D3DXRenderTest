#include "Layer.h"

Layer* Layer::create()
{
	Layer* ret = nullptr;
	gbAlloc(ret);
	ret->autorelease();
	return ret;
}

void Layer::visit()
{
	
}
