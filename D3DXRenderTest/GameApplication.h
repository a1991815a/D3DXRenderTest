#ifndef __GAMEAPPLICATION__
#define __GAMEAPPLICATION__
#include "Application.h"
#include <vector>
#include "GameStep.h"

class GameApplication: public Application{
public:
	virtual bool init() override;
};
#endif