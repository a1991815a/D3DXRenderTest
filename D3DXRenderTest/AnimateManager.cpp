#include "AnimateManager.h"

AnimateManager::AnimateManager()
{

}

AnimateManager::~AnimateManager()
{

}

bool AnimateManager::init()
{

	return true;
}

void AnimateManager::loop()
{
	auto itor = m_animate.begin();
	for (; itor != m_animate.end(); ++itor)
		itor->second->run();
}

void AnimateManager::destroy()
{
	
}

void AnimateManager::pushAnimate(const GString& str, Animate* animate)
{
	m_animate.insert(str, animate);
}

void AnimateManager::popAnimate(const GString& str)
{
	m_animate.erase(str);
}

Animate* AnimateManager::getAnimate(const GString& str)
{
	return m_animate.at(str);
}
