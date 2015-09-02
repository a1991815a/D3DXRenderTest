#include "CallFunc.h"

CallFunc::CallFunc()
	:m_func(nullptr)
{

}

CallFunc* CallFunc::create(callFunc func)
{
	CallFunc* ret = nullptr;
	gbAlloc(ret);
	ret->m_func = func;
	ret->autorelease();
	return ret;
}

void CallFunc::_update()
{
	m_func();
	setStop(true);
}

const CallFunc& CallFunc::operator=(const CallFunc& func)
{
	m_func = func.m_func;
	if (m_func != nullptr)
		isInit = true;
	return *this;
}

const CallFunc& CallFunc::operator=(callFunc func)
{
	m_func = func;
	if (m_func != nullptr)
		isInit = true;
	return *this;
}
