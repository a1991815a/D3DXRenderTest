#ifndef __ACTIONSEQUENCE__
#define __ACTIONSEQUENCE__
#include "ActionInterval.h"
#include "Vector.h"

class ActionSequence: public ActionInterval{
public:
	ActionSequence();
	static ActionSequence* create(Action* action_1, ...);

	virtual void init(Node* node) override;

	virtual void _update();
	
private:
	Vector<Action*> m_actionList;
	int m_index;
};
#endif