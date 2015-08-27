#include "Director.h"
#include "GBAssert.h"
#include "MacroHeader.h"
#include "MessageManager.h"
#include "MemoryPoolManager.h"
#include "GameUI.h"
#include "AnimateManager.h"

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
		m_scene->pushQuadCommand();
	}
}

bool Director::init(HWND hwnd)
{
	render_engine->init(hwnd);
	MessageManager::getInstance()->init();
	GameUI::getInstance()->init();
	AnimateManager::getInstance()->init();
	MemoryPoolManager::getInstance()->init();
	return true;
}

void Director::loop()
{
	MessageManager::getInstance()->loop();					//��Ϣ�ַ�
	AnimateManager::getInstance()->loop();					//��������
	update();												//����
	render_engine->loop();									//��Ⱦ

	MemoryPoolManager::getInstance()->loop();				//�ڴ����
}

void Director::destroy()
{
	delete render_engine;
	MessageManager::getInstance()->destroy();
	MemoryPoolManager::getInstance()->destroy();
}

void Director::TransformScene(Scene* scene)
{
	if(m_scene)
		m_scene->release();
	m_scene = scene;
	m_scene->retain();

}

Scene* Director::getCurrentScene()
{
	return m_scene;
}

void Director::setRenderEngine(RenderEngine* render_endgine)
{
	this->render_engine = render_endgine;
}
