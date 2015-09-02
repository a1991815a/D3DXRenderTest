#include "Action.h"
#include "ActionManager.h"
#include "MacroHeader.h"


Action::Action( ActionTypes type )
	:m_bindNode(nullptr), m_type(type), m_stop(false), isInit(false),
	m_resetAction(nullptr)
{}

Action::~Action()
{
	SAFE_RELEASE(m_bindNode);
	SAFE_RELEASE(m_resetAction);
}

void Action::init(Node* node)
{
	m_bindNode = node;
	m_bindNode->retain();
}

Action::ActionTypes Action::getActionType() const
{
	return m_type;
}

Node* Action::getNode()
{
	return m_bindNode;
}

const Node* Action::getNode() const
{
	return m_bindNode;
}
