#ifndef __SPRITE__
#define __SPRITE__
#include "Node.h"
#include "SpriteFrame.h"

class Sprite: public Node{
private:
	SpriteFrame* m_frame;
public:
	Sprite();
	~Sprite();

	virtual void visit();
	CREATE_FUNC(Sprite);
	bool init();
	void setFrame(SpriteFrame* frame);
	
private:
	void bindAnimate();
};
#endif