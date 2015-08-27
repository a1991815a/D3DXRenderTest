#ifndef __ACTIONMANAGER__
#define __ACTIONMANAGER__
#include "SingleInstance.h"
#include "GameStep.h"
#include "ActionInterval.h"
#include "ActionInstant.h"
#include "Set.h"

class ActionManager: 
	public SingleInstance<ActionManager>, 
	public GameStep{
	DEFINE_PRIVATE_INSTANCE(ActionManager);
public:
	void pushAction(Action* action);
	void popAction(Action* action);

	virtual bool init() override;
	virtual void loop() override;
	virtual void destroy() override;

private:
	Set<Action*> m_actionList;
};
#endif