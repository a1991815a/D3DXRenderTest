#ifndef __ACTIONINSTANT__
#define __ACTIONINSTANT__
#include "Action.h"

class ActionInstant: public Action{
public:
	ActionInstant();
	virtual void update() override;

	virtual void init(Node* node) override;

private:
	

	

};
#endif