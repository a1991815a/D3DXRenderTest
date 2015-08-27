#include "GameUI.h"
#include "Sprite.h"
#include "SpriteFrame.h"
#include "Director.h"
#include "Scene.h"
#include "GBCALLBACK.h"
#include "Animate.h"
#include "AnimateManager.h"
#include "GButton.h"
#include "gbLine.h"
#include "gbRect.h"
#include "SpriteFrameManager.h"

void GameUI::initStartUI()
{
	startScene = Scene::create();
	startScene->retain();
// 	GButton* gb = GButton::create("/ui/uis_57.png");
// 	
// 	GButton* gb_2 = GButton::create("/ui/uis_374.png");
// 	gb_2->setPosition(100, 100);
// 
// 	startScene->addChild(gb);
// 	gb->debug();
// 	gb->setPosition(100, 100);
// 	gb->addChild(gb_2);
// 	gb_2->debug();

//379 384
	GString pre_path = "background/bg_";
	for (int i = 12; i <= 28; ++i)
	{
		GString path = pre_path;
		path += i;
		path += ".png";
		SpriteFrameManager::getInstance()->loadSpriteFrameFromFile(path.c_str());
	}

	Sprite* sprite = Sprite::createBySpriteFrame("background/bg_22.png");
	startScene->addChild(sprite);
	sprite->setPosition(0, 0);
	sprite->setScaleToScreen(1, 1);

	pre_path = "ui/uis_";
	GButton* gb[6] = { 0 };
	for (int i = 379; i <= 384; ++i)
	{
		GString path = pre_path;
		path += i;
		path += ".png";
		SpriteFrameManager::getInstance()->loadSpriteFrameFromFile(path.c_str());
		gb[i - 379] = GButton::createFromSpriteFrame(path);
		gb[i - 379]->setPositionY(0);
		gb[i - 379]->setPositionX((i - 379) * 80);
		gb[i - 379]->setTag(i - 379);
		sprite->addChild(gb[i - 379]);
	}
	


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
