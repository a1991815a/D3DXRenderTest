#include "MessageManager.h"
#include "GBAssert.h"

MessageManager::~MessageManager()
{

}

MessageManager::MessageManager()
{

}

void MessageManager::removeEventListener( Listener* listener )
{
	ListenerNode lNode(listener);
	auto itor = m_listenerList.find(lNode);
	++itor;
	for (; itor != m_listenerList.end() && lNode.priority == (*itor).priority; ++itor)
	{
		if(lNode.listener == (*itor).listener)
		{
			delete (*itor).listener;
			m_listenerList.erase(itor);
			break;
		}
	}
	GBASSERT(false);
}

void MessageManager::clearMessage()
{
	auto itor = m_eventList.begin();
	for (; itor != m_eventList.end(); ++itor)
		delete *itor;
	m_eventList.clear();
}

void MessageManager::loop()
{
	auto eventItor = m_eventList.begin();
	for (; eventItor != m_eventList.end(); ++eventItor)
	{
		Event* event = *eventItor;
		auto listenerItor = m_listenerList.begin();
		for (; listenerItor != m_listenerList.end(); ++listenerItor)
		{
			Listener* listener = (*listenerItor).listener;
			if(listener->canTrigger(event))
				if(listener->trigger(event))
					break;
		}
	}
	
}

bool MessageManager::init()
{
	m_eventList.reserve(50);
	return true;
}

void MessageManager::destroy()
{
	clearMessage();
	auto itor = m_listenerList.begin();
	for (; itor != m_listenerList.end(); ++itor)
		delete (*itor).listener;
	m_listenerList.clear();
}
