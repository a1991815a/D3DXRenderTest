#include "ActionInstant.h"


ActionInstant::ActionInstant()
	:Action(Action::ACTION_INSTANT)
{

}



void ActionInstant::update()
{
	GBASSERT(isInit);
	this->_update();
}

void ActionInstant::init(Node* node)
{
	Action::init(node);
	isInit = true;
}
