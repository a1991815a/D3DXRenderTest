#include "MessageManager.h"
#include "GBAssert.h"
#include "MemoryPool/gbMemoryPool.h"

MessageManager::MessageManager()
{

}

MessageManager::~MessageManager()
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
			gbDealloc((*itor).listener);
			m_listenerList.erase(itor);
			break;
		}
	}
	GBASSERT(false);
}

void MessageManager::sendMessage(
	EventTypes m_eventType,
	unsigned long m_param, 
	void* m_data /*= nullptr */)
{
	Event* event = nullptr;
	gbAlloc(event);
	event->m_eventType = m_eventType;
	event->m_param = m_param;
	event->m_data = m_data;
	event->m_eventLocation = &m_location;
	this->sendMessage(event);
}

void MessageManager::sendKeyMessage(char key, KeyEventTypes key_type)
{
	switch (key_type)
	{
	case ET_KEY_DOWN:
		for (
		auto itor = m_keyList.begin();
		itor != m_keyList.end(); 
		++itor)
			if (*itor == key)
				return;
		m_keyList.push_back(key);
		break;
	case ET_KEY_UP:
	{
		for (
		auto itor = m_keyList.begin();
		itor != m_keyList.end(); 
		++itor)
			if (*itor == key)
			{
				m_keyList.erase(itor);
				break;
			};
		Event* event = nullptr;
		gbAlloc(event);
		event->m_data = nullptr;
		event->m_eventKey = key;
		event->m_eventLocation = &m_location;
		event->m_eventType = ET_KEY;
		event->m_param = ET_KEY_UP;
		sendMessage(event);
	}
		break;
	default:
		break;
	}
}

void MessageManager::sendMouseMessage(float x, float y, MouseEventTypes mouse_type)
{
	switch (mouse_type)
	{
	case ET_MOUSE_LDOWN:
	{
		Event* event = nullptr;
		gbAlloc(event);
		event->m_data = nullptr;
		event->m_eventLocation = &m_location;
		event->m_eventType = ET_MOUSE;
		event->m_param = ET_MOUSE_LDOWN;
		sendMessage(event);
	}
		break;
	case ET_MOUSE_LUP:
	{
		Event* event = nullptr;
		gbAlloc(event);
		event->m_data = nullptr;
		event->m_eventLocation = &m_location;
		event->m_eventType = ET_MOUSE;
		event->m_param = ET_MOUSE_LUP;
		sendMessage(event);
	}
		break;
	case ET_MOUSE_MOVE:
	{
		m_location.x = x;
		m_location.y = y;
		Event* event = nullptr;
		gbAlloc(event);
		event->m_data = nullptr;
		event->m_eventLocation = &m_location;
		event->m_eventType = ET_MOUSE;
		event->m_param = ET_MOUSE_MOVE;
		sendMessage(event);
	}
		break;
	default:
		break;
	}
}

void MessageManager::clearMessage()
{
	auto itor = m_eventList.begin();
	for (; itor != m_eventList.end(); ++itor)
		gbDealloc(*itor);
	m_eventList.clear();
}

void MessageManager::loop()
{
	for (
		auto itor = m_keyList.begin();
		itor != m_keyList.end();
		++itor	)
	{
		size_t ss = m_keyList.size();
		Event* event = nullptr;
		gbAlloc(event);
		event->m_data = nullptr;
		event->m_eventKey = *itor;
		event->m_eventLocation = &m_location;
		event->m_eventType = ET_KEY;
		event->m_param = ET_KEY_DOWN;
		sendMessage(event);
	}
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
	clearMessage();
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
		gbDealloc((*itor).listener);
	m_listenerList.clear();
}
