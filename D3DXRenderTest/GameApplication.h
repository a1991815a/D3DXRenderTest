#ifndef __GAMEAPPLICATION__
#define __GAMEAPPLICATION__
#include "Application.h"

class GameApplication: public Application{
public:
	virtual void init() override;

	virtual int run() override;

	virtual void destroy() override;

};
#endif