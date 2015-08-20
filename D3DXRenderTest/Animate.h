#ifndef __ANIMATE__
#define __ANIMATE__
#include "Animation.h"
#include <unordered_map>

class Animate: public Ref{
private:
	struct Timer_Frame{
		Timer_Frame():cur_frame(0){};
		size_t cur_frame;
		Timer m_timer;
	};
private:
	Animation* animation;

	std::unordered_map<SpriteFrame**, Timer_Frame> m_useIndex;
public:
	void setAnimation(Animation* ani){
		animation = ani;
	};
	const Animation* getAnimation() const{
		return animation;
	}
	
	void bindSpriteFrame(SpriteFrame** frame);
	void update();
};
#endif