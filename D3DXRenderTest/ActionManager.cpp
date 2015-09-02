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
	

	return true;
}

void ActionManager::loop()
{
	auto itor = m_actionList.begin();
	for (; itor != m_actionList.end(); )
	{
		(*itor)->update();
		if((*itor)->getStop())
			if((itor = m_actionList.erase(itor)) == m_actionList.end())
				break;
		++itor;
	}
}

void ActionManager::destroy()
{
	m_actionList.clear();
}
