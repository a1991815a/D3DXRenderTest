#ifndef __ACTIONREPEAT__
#define __ACTIONREPEAT__
#include "ActionInterval.h"

class ActionRepeat: public ActionInterval{
public:
	static ActionRepeat* create(Action* _action);

	ActionRepeat();
	ActionRepeat(const ActionRepeat& action_repeat);
	~ActionRepeat();

	virtual void init(Node* node) override;

	virtual void _update();

private:
	Action* repeat_action;
};
#endif