#include "ActionSequence.h"
#include <stdarg.h>

ActionSequence::ActionSequence()
	:m_index(0)
{

}

ActionSequence* ActionSequence::create(Action* action_1, ...)
{
	ActionSequence* ret = nullptr;
	gbAlloc(ret);

	va_list ap;
	va_start(ap, action_1);
	if(action_1 != nullptr)
		ret->m_actionList.push_back(action_1);
	Action* action = nullptr;
	while ( (action = va_arg(ap, Action*)) != nullptr)
		ret->m_actionList.push_back(action);
	va_end(ap);

	ret->autorelease();
	return ret;
}

void ActionSequence::init(Node* node)
{
	ActionInterval::init(node);
	m_actionList.front()->init(node);
}

void ActionSequence::_update()
{
	Action* action = m_actionList.at(m_index);
	action->update();
	if(action->getStop())
	{
		if(++m_index >= m_actionList.size())
			setStop(true);
		else
			m_actionList.at(m_index)->init(action->getNode());
	}
}
