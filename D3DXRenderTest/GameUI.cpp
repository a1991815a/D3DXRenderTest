#include "GameUI.h"
#include "Sprite.h"
#include "SpriteFrame.h"
#include "Director.h"
#include "Scene.h"
#include "GBCALLBACK.h"

void GameUI::initStartUI()
{
	startScene = Scene::create();
	startScene->retain();
	SpriteFrame* sf = SpriteFrame::create("ShareWeiboImage.jpg");
	Sprite* back_ground = Sprite::create();
	back_ground->setFrame(sf);
	startScene->addChild(back_ground);
	back_ground->setPosition(0, 0);
	back_ground->setScaleY(700.0f/480.0f);
	_director->TransformScene(startScene);
}

void GameUI::StartUI( void* )
{
	if(_director->getCurrentScene() != startScene)
		_director->TransformScene(startScene);
}

void GameUI::EndUI( void* )
{

}

bool GameUI::init()
{
	registerState(0, GBCALLBACK_1(GameUI::StartUI, this));
	setState(0);
	initStartUI();
	return true;
}

void GameUI::loop()
{
	RunStateFunc(nullptr);
}

void GameUI::destroy()
{
	startScene->release();
}
