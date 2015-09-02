#ifndef __ACTION__
#define __ACTION__
#include "Node.h"


class Action: public Ref{
	friend class Node;
	friend class ActionRepeat;
	friend class ActionSequence;
public:
	enum ActionTypes{
		ACTION_INSTANT,
		ACTION_INTERVAL
	};
public:
	Action(ActionTypes type);
	~Action();

//执行方式
	virtual void update() = 0;

	ActionTypes getActionType() const;

	void setStop(bool _stop){
		m_stop = _stop;
	};
	bool getStop() const{
		return m_stop;
	};

	const Node* getNode() const;

protected:
//执行内容
	virtual void _update() = 0;
	
	
	Node* getNode();
	
	virtual void init(Node* node);
private:
	Node* m_bindNode;
	ActionTypes m_type;
	bool m_stop;

	Action* m_resetAction;
protected:
	bool isInit;
};
#endif