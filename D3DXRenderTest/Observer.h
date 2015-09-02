#ifndef __OBSERVER__
#define __OBSERVER__
#include "UtilsHeader.h"
#include <functional>

typedef std::function<void(const GString&, long param, void* obj)> observerFunc;

class Observer{
	friend class ObserverSystem;
private:
	typedef std::unordered_map<GString, observerFunc>::value_type value_type;
public:
	Observer();
	~Observer();

	void addObserver(const GString& str, observerFunc func);

protected:
	virtual void initObserver() = 0;
private:
	std::unordered_map<GString, observerFunc> m_msgList;
	observerFunc* findObserve(const GString& msg);
};
#endif