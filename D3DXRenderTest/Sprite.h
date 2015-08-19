#ifndef __SPRITE__
#define __SPRITE__
#include "Node.h"
#include "Texture2D.h"

class Sprite: public Node{
private:
	Texture2D* m_texture;
public:
	Sprite();
	~Sprite();

	virtual void visit();
	CREATE_FUNC(Sprite);
	bool init();
	void setFrame(Texture2D* texture);
	
private:
	void bindAnimate();
};
#endif