#ifndef __GAMEUI__
#define __GAMEUI__
#include "LimitStateMachine.h"
#include "Scene.h"
#include "GameStep.h"
#include "SingleInstance.h"
#include "UtilsHeader.h"
#include "MouseListener.h"

#define START_SCENE_ID		1
#define FIGHT_SCENE_ID		2
#define STRATEGIC_SCENE_ID	3
#define GROUND_SCENE_ID		4
#define AIR_SCENE_ID		5
#define SKILL_SCENE_ID		6
#define BASE_SCENE_ID		7
#define HERO_SCENE_ID		8


class GameUI: 
	public SingleInstance<GameUI>, 
	public LimitStateMachine, 
	public GameStep{
public:
	GameUI();
	~GameUI();
	
	void initStartUI();
	void loadResource();

	void runUI(long, void*);

	virtual bool init();

	virtual void loop();

	virtual void destroy();
	
	void EnableEdtit(bool flag);
private:
	Scene* startScene;
	Scene* actorFightScene;
	Scene* strategicFightScene;


	Scene* groundStore;
	Scene* airStore;
	Scene* skillStore;
	Scene* baseStore;
	Scene* heroStore;

	void initStore();






private:
	MouseListener* edit_listener;
	void initEditor();
	Node* sel_node;
	Node* pre_node;
	bool isLocked;
	Vec2 pre_location;
};
#endif