#ifndef __SPRITE__
#define __SPRITE__
#include "Node.h"
#include "SpriteFrame.h"


class Sprite: public Node{
	friend class Animate;
private:
	SpriteFrame* m_frame;

public:
	CREATE_FUNC(Sprite);
	static Sprite* createBySpriteFrame(const GString& key);
public:
	Sprite();
	~Sprite();

	virtual void visit();
	
	bool init();
	void setFrame(SpriteFrame* frame);
	
private:
	void bindAnimate();
};
#endif