#include "Action.h"
#include "ActionManager.h"


Action::Action( ActionTypes type )
	:m_bindNode(nullptr), m_type(type)
{

}

Action::~Action()
{
	if(m_bindNode)
		m_bindNode->release();
}

void Action::bindNode(Node* node)
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

void Action::setStop()
{
	ActionManager::getInstance()->popAction(this);
}
