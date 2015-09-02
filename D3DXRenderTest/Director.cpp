#include "Director.h"
#include "GBAssert.h"
#include "MacroHeader.h"
#include "MessageManager.h"
#include "MemoryPoolManager.h"
#include "GameUI.h"
#include "AnimateManager.h"
#include "ActionManager.h"
#include "TimerManager.h"
#include "Win32Utils.h"

Director::Director()
	:m_scene(nullptr)
{

}

Director::~Director()
{

}

void Director::update()
{
	GameUI::getInstance()->loop();
	if (m_scene)
	{
		m_scene->update();
		getD3DXRenderEngine()->m_globalList.clear();
		getD3DXRenderEngine()->m_localList.clear();
		m_scene->pushQuadCommand();
	}
}

bool Director::init(HWND hwnd)
{
	MemoryPoolManager::getInstance()->init();

	TimerManager::getInstance()->init();	//时间管理器初始化
	render_engine->init(hwnd);
	MessageManager::getInstance()->init();
	GameUI::getInstance()->init();
	/*动画系统
	AnimateManager::getInstance()->init();
	已内置到ActionManager
	*/
	ActionManager::getInstance()->init();
	
	return true;
}

void Director::loop()
{
	MessageManager::getInstance()->loop();					//消息分发
	/*动画系统
	AnimateManager::getInstance()->loop();					
	已内置到ActionManager
	*/
	ActionManager::getInstance()->loop();					//动作更新
	update();												//绘图数据更新
	render_engine->loop();									//渲染

	MemoryPoolManager::getInstance()->loop();				//引用内存清理				
}

void Director::destroy()
{
	delete render_engine;
	ActionManager::getInstance()->destroy();
	MessageManager::getInstance()->destroy();
	MemoryPoolManager::getInstance()->destroy();
}

Vec2 Director::getWindowSize() const
{
	Win32Utils* w32 = Win32Utils::getInstance();
	return Vec2(w32->getWidth(), w32->getHeight());
}

void Director::TransformScene(Scene* scene)
{
	if(m_scene)
	{
		m_scene->release();
		m_scene->setEnable(false);
	}
	m_scene = scene;
	m_scene->retain();
	m_scene->setEnable(true);
	m_scene->setVisiable(true);
}

Scene* Director::getCurrentScene()
{
	return m_scene;
}

void Director::setRenderEngine(RenderEngine* render_endgine)
{
	this->render_engine = render_endgine;
}
