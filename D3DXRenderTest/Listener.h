#ifndef __LISTENER__
#define __LISTENER__
#include "GBCALLBACK.h"
#include "Event.h"
#include <vector>

typedef std::function<bool(Event*)> listenerFunc;

class Listener{
	friend class MessageManager;
private:
	int m_priority;
	std::vector<EventTypes> m_listenerTypeList;
public:
	Listener(EventTypes type = ET_UNKNOWN, int priority = 0){ 
		m_priority = priority; 
		m_listenerTypeList.push_back(type);
	};
	virtual ~Listener(){};
	inline int getPriority() const{return m_priority;};
	virtual bool trigger(Event* event) = 0;

	bool canTrigger(Event* event){
		auto itor = m_listenerTypeList.begin();
		for (; itor != m_listenerTypeList.end(); ++itor)
			if(*itor == event->getType())
				return true;
		return false;
	};
};

#endif