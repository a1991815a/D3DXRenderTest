#include "ActionInstant.h"


ActionInstant::ActionInstant()
	:Action(Action::ACTION_INSTANT)
{

}



void ActionInstant::update()
{
	if(!getPause())
		this->_update();
}
