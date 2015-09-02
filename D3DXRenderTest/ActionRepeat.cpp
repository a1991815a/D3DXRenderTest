// #include "ActionRepeat.h"
// #include "MacroHeader.h"
// 
// ActionRepeat* ActionRepeat::create(Action* _action)
// {
// 	ActionRepeat* ret = nullptr;
// 	gbAlloc(ret);
// 	ret->repeat_action = _action;
// 	ret->repeat_action->retain();
// }
// 
// ActionRepeat::ActionRepeat()
// 	:repeat_action(nullptr)
// {
// 
// }
// 
// ActionRepeat::ActionRepeat(const ActionRepeat& action_repeat)
// {
// 
// }
// 
// ActionRepeat::~ActionRepeat()
// {
// 	SAFE_RELEASE(repeat_action);
// }
// 
// void ActionRepeat::init(Node* node)
// {
// 	ActionInterval::init(node);
// 	repeat_action->init(node);
// 	repeat_action->initResetVal();
// }
// 
// void ActionRepeat::_update()
// {
// 	repeat_action->_update();
// 	if(repeat_action->getStop())
// 		repeat_action->Reset();
// }
