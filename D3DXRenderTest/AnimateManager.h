#ifndef __ANIMATEMANAGER__
#define __ANIMATEMANAGER__
#include "SingleInstance.h"
#include "Map.h"
#include "Animate.h"

#define _animateManager AnimateManager::getInstance()

class AnimateManager: public SingleInstance<AnimateManager>{
	DEFINE_PRIVATE_INSTANCE(AnimateManager);
public:
	void pushAnimate(const GString& str, Animate* animate);
	void popAnimate(const GString& str);
	Animate* getAnimate(const GString& str);

private:
	Map<GString, Animate*> m_animate;
};
#endif