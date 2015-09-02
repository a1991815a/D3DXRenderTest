#ifndef __OBSERVERSYSTEM__
#define __OBSERVERSYSTEM__
#include "SingleInstance.h"
#include "UtilsHeader.h"
#include "Observer.h"
#include <unordered_set>

#define _observerSystem			ObserverSystem::getInstance()

class ObserverSystem: public SingleInstance<ObserverSystem>{
	DEFINE_PRIVATE_INSTANCE(ObserverSystem);
	typedef std::unordered_set<Observer*>::iterator iterator;
	typedef std::unordered_set<Observer*>::const_iterator const_iterator;
public:
	void addObserver(Observer* observer);
	bool existObserver(Observer* observer);
	void removeObserver(Observer* observer);
	void removeMessage(const GString& msg);
	void clearObserver();

	void sendMessage(const GString& msg, long param = 0, void* data = nullptr);
private:
	std::unordered_set<Observer*> m_observerList;
	iterator m_itor;
};
#endif