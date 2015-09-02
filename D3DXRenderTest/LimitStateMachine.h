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
typedef std::function<void(long, void*)> LimitStateFunc;

class LimitStateMachine{
private:
	struct StateNode {
		StateNode(LimitStateFunc func = nullptr, long param = 0, void* data = nullptr)
			:func(func), param(param), data(data)
		{};
		LimitStateFunc func;
		long param;
		void* data;
	};
private:
	std::unordered_map<limitState, StateNode> m_funcList;
	limitState m_State;
	StateNode* m_curStateNode;
public:
	inline LimitStateMachine()
		:m_State(0), m_curStateNode(nullptr)
	{};

	inline virtual ~LimitStateMachine(){};

	inline void setState(limitState state){
		auto itor = m_funcList.find(state);
		GBASSERT(itor != m_funcList.end());
		m_State = state;
		m_curStateNode = (StateNode*)(&itor->second);
	};

	inline limitState getState() const{
		return m_State;
	};

	inline void registerState(limitState _State, LimitStateFunc func, long param = 0, void* data = nullptr){
		GBASSERT(m_funcList.find(_State) == m_funcList.end());
		m_funcList.insert(
			std::unordered_map<limitState, StateNode>::value_type(
				_State,
				StateNode(func, param, data)
			));
	}

	inline void unregisterState(limitState _State){
		GBASSERT(m_funcList.find(_State) != m_funcList.end());
		m_funcList.erase(_State);
	}

	inline void RunStateFunc(){
		GBASSERT(m_curStateNode != nullptr);
		m_curStateNode->func(
			m_curStateNode->param,
			m_curStateNode->data
			);
	}
};
#endif