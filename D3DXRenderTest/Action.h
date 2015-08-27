#ifndef __ACTION__
#define __ACTION__
#include "Node.h"



class Action: public Ref{
	friend class Node;
public:
	enum ActionTypes{
		ACTION_INSTANT,
		ACTION_INTERVAL
	};
public:
	Action(ActionTypes type);
	~Action();

//ִ�з�ʽ
	virtual void update() = 0;

	ActionTypes getActionType() const;
	void setStop();
protected:
//ִ������
	virtual void _update() = 0;
	void bindNode(Node* node);
	
	Node* getNode();
	const Node* getNode() const;
private:
	Node* m_bindNode;
	ActionTypes m_type;
};
#endif