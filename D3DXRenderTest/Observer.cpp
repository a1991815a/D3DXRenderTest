#include "Observer.h"
#include "ObserverSystem.h"
#include "GBAssert.h"

Observer::Observer()
{
	ObserverSystem::getInstance()->addObserver(this);
/*	this->initObserver();*/
}

Observer::~Observer()
{
	ObserverSystem::getInstance()->removeObserver(this);
}

void Observer::addObserver(const GString& str, observerFunc func)
{
	GBASSERT(!str.empty() && func != nullptr);
	m_msgList.insert(value_type(str, func));
}

observerFunc* Observer::findObserve(const GString& msg)
{
	auto itor = m_msgList.find(msg);
	if (itor == m_msgList.end())
		return nullptr;
	return &itor->second;
}
