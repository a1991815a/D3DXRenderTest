#ifndef __CALLFUNC__
#define __CALLFUNC__
#include "ActionInstant.h"
#include <functional>

typedef std::function<void(void)> callFunc;

class CallFunc: public ActionInstant{
public:
	CallFunc();
	static CallFunc* create(callFunc func);

	const CallFunc& operator=(callFunc func);
	const CallFunc& operator=(const CallFunc& func);

	
protected:
	virtual void _update() override;

private:
	callFunc m_func;
};
#endif