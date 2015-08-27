#include "ActionManager.h"

ActionManager::ActionManager()
{

}

ActionManager::~ActionManager()
{
	m_actionList.clear();
}

void ActionManager::pushAction( Action* action )
{
	m_actionList.insert(action);
}

void ActionManager::popAction( Action* action )
{
	m_actionList.erase(action);
}

bool ActionManager::init()
{
	
}

void ActionManager::loop()
{
	auto itor = m_actionList.begin();
	for (; itor != m_actionList.end(); ++itor)
		(*itor)->update();
}

void ActionManager::destroy()
{
	m_actionList.clear();
}
