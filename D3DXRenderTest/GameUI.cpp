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
#include "Move.h"
#include "CallFunc.h"
#include "Scale.h"
#include "Rotate.h"
#include "ActionSequence.h"
#include "TimeDelay.h"
#include "KeyListener.h"
#include "MessageManager.h"
#include "MacroHeader.h"
#include "Shake.h"
#include "Layer.h"
#include "Number.h"

GameUI::GameUI()
	:edit_listener(nullptr), sel_node(nullptr), pre_node(nullptr), isLocked(false)
{
	startScene = Scene::create();
	startScene->retain();
	actorFightScene = Scene::create();
	actorFightScene->retain();
	strategicFightScene = Scene::create();
	strategicFightScene->retain();
}

GameUI::~GameUI()
{
	SAFE_RELEASE(startScene);
	SAFE_RELEASE(actorFightScene);
	SAFE_RELEASE(strategicFightScene);
}

void GameUI::initStartUI()
{
	Sprite* background = Sprite::createBySpriteFrame("background/bg_22.png");

	Layer* layer = Layer::create();
	background->addChild(layer);

	GButton* gb[6];

	gb[0] = GButton::createByKey("new_game");
	gb[1] = GButton::createByKey("start_game");
	gb[2] = GButton::createByKey("special_game");
	gb[3] = GButton::createByKey("setting_game");
	gb[4] = GButton::createByKey("rank_game");
	gb[5] = GButton::createByKey("help_game");

	for (int i = 0; i < 6; ++i)
	{
// 		GString path = "ui/uis_";
// 		path += i + 379;
// 		path += ".png";
// 		gb[i] = GButton::create(path);
		gb[i]->setPositionY(0);
		gb[i]->setPositionX(background->getContentSize().x / 6 * i);
		layer->addChild(gb[i]);
	}

	gb[0]->onHit = [background, layer, this](Event* e)->bool {
		GameUI* ui = this;

		Animate* animate = Animate::create();
		animate->addSpriteFrameByName("background/bg_12.png");
		animate->addSpriteFrameByName("background/bg_13.png");
		animate->addSpriteFrameByName("background/bg_14.png");
		animate->addSpriteFrameByName("background/bg_15.png");
		animate->addSpriteFrameByName("background/bg_16.png");
		animate->setDelay(1000);
		animate->setReplay(false);
		animate->setReset(false);

		Animate* animate_2 = Animate::create();
		animate_2->addSpriteFrameByName("background/bg_17.png");
		animate_2->addSpriteFrameByName("background/bg_18.png");
		animate_2->addSpriteFrameByName("background/bg_19.png");
		animate_2->setDelay(1000);
		animate_2->setReplay(false);
		animate_2->setReset(false);

		Animate* animate_3 = Animate::create();
		animate_3->addSpriteFrameByName("background/bg_20.png");
		animate_3->addSpriteFrameByName("background/bg_21.png");
		animate_3->addSpriteFrameByName("background/bg_62.png");
		animate_3->setDelay(1000);
		animate_3->setReplay(false);
		animate_3->setReset(false);


		Vec2 position = background->getPosition();

		layer->setVisiable(false);
		background->setFrame(animate->getFrame(0));
		background->runAction(
			ActionSequence::create(
			animate,
			MoveBy::create(
				0,
				background->getContentSize().y - _director->getWindowSize().y,
				3000),
				TimeDelay::create(1000),
				CallFunc::create([=](){
					background->setPosition(position);
					background->setFrameByName("background/bg_17.png");
				}),
				animate_2,
				Shake::create(5, 80, 3000),
				animate_3,
				CallFunc::create([ui](){
					ui->setState(HERO_SCENE_ID);
				}),
			nullptr
			),
			nullptr);
		return true;
	};

	background->setScaleToScreen(1, 1);
	startScene->addChild(background);
	startScene->setEnable(false);
	


}

void GameUI::loadResource()
{
	SpriteFrameManager* sfm = SpriteFrameManager::getInstance();
	sfm->loadSpriteFrameByXml("../img.xml");

	GString pre_path = "background/bg_";
	for (int i = 0; i <= 82; ++i)
	{
		GString path = pre_path;
		path += i;
		path += ".png";
		sfm->loadSpriteFrameFromFile(path);
	}

	pre_path = "ui/uis_";
	for (int i = 0; i <= 392; ++i)
	{
		GString path = pre_path;
		path += i;
		path += ".png";
		sfm->loadSpriteFrameFromFile(path);
	}
	sfm->loadSpriteFrameFromFile("ui/left_bt.png");
	sfm->loadSpriteFrameFromFile("ui/right_bt.png");

}

void GameUI::runUI(long id, void*)
{
	if(getState() == id)
		return;
	switch(getState()){
	case START_SCENE_ID:
		_director->TransformScene(startScene);
		break;
	case FIGHT_SCENE_ID:
		_director->TransformScene(actorFightScene);
		break;
	case STRATEGIC_SCENE_ID:
		_director->TransformScene(strategicFightScene);
		break;
	case GROUND_SCENE_ID:
		_director->TransformScene(groundStore);
		break;
	case AIR_SCENE_ID:
		_director->TransformScene(airStore);
		break;
	case SKILL_SCENE_ID:
		_director->TransformScene(skillStore);
		break;
	case BASE_SCENE_ID:
		_director->TransformScene(baseStore);
		break;
	case HERO_SCENE_ID:
		_director->TransformScene(heroStore);
		break;
	default:
		GBASSERT(false);
		break;
	};
}

bool GameUI::init()
{
	EnableEdtit(true);
	loadResource();
	registerState(START_SCENE_ID, GBCALLBACK_2(GameUI::runUI, this), getState());
	registerState(FIGHT_SCENE_ID, GBCALLBACK_2(GameUI::runUI, this), getState());
	registerState(STRATEGIC_SCENE_ID, GBCALLBACK_2(GameUI::runUI, this), getState());
	registerState(GROUND_SCENE_ID, GBCALLBACK_2(GameUI::runUI, this), getState());
	registerState(AIR_SCENE_ID, GBCALLBACK_2(GameUI::runUI, this), getState());
	registerState(SKILL_SCENE_ID, GBCALLBACK_2(GameUI::runUI, this), getState());
	registerState(BASE_SCENE_ID, GBCALLBACK_2(GameUI::runUI, this), getState());
	registerState(HERO_SCENE_ID, GBCALLBACK_2(GameUI::runUI, this), getState());
	setState(HERO_SCENE_ID);


// 
// 	{
// 		MouseListener* listener_2 = nullptr;
// 		gbAlloc(listener_2);
// 		listener_2->OnMouseDown = [](Event* e) {
// 			GString text = "X: ";
// 			text += e->getLocation().x;
// 			text += "  Y:";
// 			text += e->getLocation().y;
// 			text += " \n";
// 			OutputDebugStringA(text.c_str());
// 			return false;
// 		};
// 		_dispatchMessage->addEventListener(listener_2);
// 	}

	initStartUI();

	initStore();
	return true;
}

void GameUI::loop()
{
	RunStateFunc();
}

void GameUI::destroy()
{
	startScene->release();
}

void GameUI::initStore()
{
	SpriteFrameManager* sfm = SpriteFrameManager::getInstance();

	Vec2 winSize = _director->getWindowSize();

	groundStore = Scene::create();
	airStore = Scene::create();
	skillStore = Scene::create();
	baseStore = Scene::create();
	heroStore = Scene::create();

	groundStore->retain();
	airStore->retain();
	skillStore->retain();
	baseStore->retain();
	heroStore->retain();

	{
		Sprite* heroStore_bg = Sprite::createBySpriteFrame("background/bg_47.png");
		heroStore->addChild(heroStore_bg);
		heroStore_bg->setScaleToScreen(1, 1);
		Sprite* actor_select = Sprite::createBySpriteFrame("ui/uis_224.png");
		heroStore_bg->addChild(actor_select);
		actor_select->setPositionToScreen(0.1f, 0.18333f);



// 		Sprite* ss = Sprite::create();
// 		ss->setFrame(sfm->getFrameByVMap("image", "button", "new_game", sfm->endTag()));
// 
// 		ss->setPositionToScreen(0.4, 0.4);
// 		heroStore_bg->addChild(ss);

/*		GButton* l_bt = GButton::createFromSpriteFrame("ui/left_bt.png");*/
// 		GButton* r_bt = GButton::createFromSpriteFrame("ui/right_bt.png");
// 		GButton* back_bt = GButton::createFromSpriteFrame("ui/uis_243.png");
		GButton* l_bt = GButton::createByKey("left_bt");
		GButton* r_bt = GButton::createByKey("right_bt");
		GButton* back_bt = GButton::createByKey("back_bt");



		l_bt->setPositionToScreen(0.0325f, 0.2583f);
		r_bt->setPositionToScreen(0.5675f, 0.2583f);
		back_bt->setPositionToScreen(0.5662f, 0.4833f);
		l_bt->setAnchontPoint(0.5, 0.5);
		r_bt->setAnchontPoint(0.5, 0.5);
		back_bt->setAnchontPoint(0.5f, 0.5f);

		heroStore_bg->addChild(l_bt);
		heroStore_bg->addChild(r_bt);
		heroStore_bg->addChild(back_bt);
		Animate* animate = Animate::create();

		Sprite* sp = Sprite::createByKey("image", "ui", "ui_sp", sfm->endTag());

		heroStore_bg->addChild(sp);

		for (int i = 224; i <= 233; ++i)
		{
			GString text = "ui/uis_";
			text += i;
			text += ".png";
			animate->addSpriteFrameByName(text.c_str());
		}
		
		l_bt->onHit = [animate, actor_select](Event*)->bool{
			actor_select->setFrame(animate->preFrame());
			return false;
		};

		r_bt->onHit = [animate, actor_select](Event*)->bool{
			actor_select->setFrame(animate->nextFrame());
			return false;
		};

		Number* number = Number::create(Number::WHITE_SM, true);
		heroStore_bg->addChild(number);
		number->setValue(999);
		
		KeyListener* listener = nullptr;
		gbAlloc(listener);
		listener->OnKeyDown = [number](Event* e)->bool {
			switch (e->getKey()) {
			case 'W':
				number->setPositionY(number->getPosition().y + 1);
				break;
			case 'S':
				number->setPositionY(number->getPosition().y - 1);
				break;
			case 'A':
				number->setPositionX(number->getPosition().x - 1);
				break;
			case 'D':
				number->setPositionX(number->getPosition().x + 1);
				break;
			default:
				break;
			};
// 			GString text;
// 			text += "X: ";
// 			text += number->getPosition().x;
// 			text += "  Y:";
// 			text += number->getPosition().y;
// 			text += "\n";
// 			OutputDebugStringA(text.c_str());
			return true;
		};
		_dispatchMessage->addEventListener(listener);
	}



}

void GameUI::EnableEdtit(bool flag)
{
	if(flag)
	{
		if(edit_listener == nullptr)
		{
			gbAlloc(edit_listener);
			initEditor();
			_dispatchMessage->addEventListener(edit_listener);
		}
	}else{
		if(edit_listener){
			_dispatchMessage->removeEventListener(edit_listener);
			edit_listener = nullptr;
		}
	}
}

void GameUI::initEditor()
{
	edit_listener->OnMouseDown = 
		[this](Event* e)->bool{
			Node* node = _director->getD3DXRenderEngine()->HitTest(e->getLocation());
			if(node)
			{
				pre_node = sel_node;
				sel_node = node;
				if(sel_node == pre_node)
				{
					isLocked = true;
					pre_location = e->getLocation();
				}else if(sel_node != pre_node)
				{
					if(pre_node)
						pre_node->debug(false);
				}
				
				sel_node->debug(true);
			}
			return false;
	};
	edit_listener->OnMouseMove = 
		[this](Event* e)->bool{
			if(isLocked)
			{
				Vec2 trans = e->getLocation() - pre_location;
				trans.x /= 1.6666;
				trans.y /= 1.875;
				sel_node->setPosition(sel_node->getPosition() + trans);
				pre_location = e->getLocation();
			}
			return false;
	};
	edit_listener->OnMouseUp = 
		[this](Event* e)->bool{
			if(isLocked)
			{
				isLocked = false;
				GString text = "";
				text += sel_node->getPosition().x;
				text += ", ";
				text += sel_node->getPosition().y;
				text += "\n";
				OutputDebugStringA(text.c_str());
				
			}
			return false;
	};
}
