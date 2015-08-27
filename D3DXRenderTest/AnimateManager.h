#ifndef __ANIMATEMANAGER__
#define __ANIMATEMANAGER__
#include "SingleInstance.h"
#include "GameStep.h"
#include "Map.h"
#include "Animate.h"

#define _animateManager AnimateManager::getInstance()

class AnimateManager: public SingleInstance<AnimateManager>, public GameStep{
	DEFINE_PRIVATE_INSTANCE(AnimateManager);
public:
	virtual bool init() override;

	virtual void loop() override;

	virtual void destroy() override;

	void pushAnimate(const GString& str, Animate* animate);
	void popAnimate(const GString& str);
	Animate* getAnimate(const GString& str);

private:
	Map<GString, Animate*> m_animate;
};
#endif