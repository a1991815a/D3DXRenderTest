#ifndef __GAMEUI__
#define __GAMEUI__
#include "LimitStateMachine.h"
#include "Scene.h"
#include "GameStep.h"
#include "SingleInstance.h"

class GameUI: 
	public SingleInstance<GameUI>, 
	public LimitStateMachine, 
	public GameStep{
public:
	
	void initStartUI();
	

	void StartUI(void*);
	void EndUI(void*);

	virtual bool init();

	virtual void loop();

	virtual void destroy();
private:
	Scene* startScene;
};
#endif