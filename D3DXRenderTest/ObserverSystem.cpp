#include "ObserverSystem.h"
#include "GBAssert.h"

ObserverSystem::ObserverSystem()
{
	m_itor = m_observerList.end();
}

ObserverSystem::~ObserverSystem()
{
	clearObserver();
}

void ObserverSystem::addObserver(Observer* observer)
{
	GBASSERT(observer != nullptr);
	m_observerList.insert(observer);
}

bool ObserverSystem::existObserver(Observer* observer)
{
	if (m_observerList.find(observer) == m_observerList.end())
		return false;
	return true;
}

void ObserverSystem::removeObserver(Observer* observer)
{
	GBASSERT(observer != nullptr);
	const_iterator itor = m_observerList.find(observer);
	if (m_itor == m_observerList.end())
		return;
	m_itor = m_observerList.erase(itor);
	if (m_itor != m_observerList.begin())
		--m_itor;
}

void ObserverSystem::removeMessage(const GString& msg)
{
	m_itor = m_observerList.begin();
	while (m_itor != m_observerList.end())
	{
		Observer* observer = (*m_itor);
		auto msg_itor = observer->m_msgList.begin();
		while (msg_itor != observer->m_msgList.end())
		{
			if(msg_itor->first != msg)
				++msg_itor;
			else
				msg_itor = observer->m_msgList.erase(msg_itor);
		}

		if (observer->m_msgList.empty())
			removeObserver(*m_itor);
		if(m_itor != m_observerList.end())
			++m_itor;
	}

}

void ObserverSystem::clearObserver()
{
	m_observerList.clear();
}

void ObserverSystem::sendMessage(const GString& msg, long param /*= 0*/, void* data /*= nullptr*/)
{
	GBASSERT(!msg.empty());
	m_itor = m_observerList.begin();
	while (m_itor != m_observerList.end())
	{
		Observer* observer = *m_itor;
		observerFunc* func = nullptr;
		if ((func = observer->findObserve(msg)) != nullptr)
			(*func)(msg, param, data);
		if (m_itor != m_observerList.end())
			++m_itor;
	}
}