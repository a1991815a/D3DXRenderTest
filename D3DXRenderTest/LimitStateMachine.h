#ifndef __LIMITSTATEMACHINE__
#define __LIMITSTATEMACHINE__
#include "GBCALLBACK.h"
#include <unordered_map>
#include "GBAssert.h"

/*
	ÓÐÏÞ×´Ì¬»ú:
	version: 1.0
*/

typedef unsigned int limitState;
typedef std::function<void(void*)> LimitStateFunc;

class LimitStateMachine{
private:
	std::unordered_map<limitState, LimitStateFunc> m_funcList;
	limitState m_State;
	LimitStateFunc* m_curFunc;
public:
	inline LimitStateMachine()
		:m_State(0), m_curFunc(nullptr)
	{};

	inline virtual ~LimitStateMachine(){};

	inline void setState(limitState state){
		auto itor = m_funcList.find(state);
		GBASSERT(itor != m_funcList.end());
		m_State = state;
		m_curFunc = (LimitStateFunc*)(&itor->second);
	};

	inline limitState getState() const{
		return m_State;
	};

	void registerState(limitState _State, LimitStateFunc func){
		GBASSERT(m_funcList.find(_State) == m_funcList.end());
		m_funcList.insert(
			std::unordered_map<limitState, LimitStateFunc>::value_type(_State, func)
			);
	}

	void unregisterState(limitState _State){
		GBASSERT(m_funcList.find(_State) != m_funcList.end());
		m_funcList.erase(_State);
	}

	inline void RunStateFunc(void* data){
		GBASSERT(m_curFunc != nullptr);
		(*m_curFunc)(data);
	}
};
#endif