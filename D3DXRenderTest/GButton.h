#ifndef __GBUTTON__
#define __GBUTTON__
#include "Node.h"
#include "D3DXHeader.h"
#include "Vec.h"
#include "SpriteFrame.h"
#include "MouseListener.h"
#include "Listener.h"


class GButton: public Node{
public:
	listenerFunc onHit;
	listenerFunc onMoveIn;
public:
	GButton();
	~GButton();
	static GButton* create(const GString& image_path);
	static GButton* createFromSpriteFrame(const GString& _frame);

	virtual void visit() override;
private:
	bool HitTest(const Vec2& point) const;
private:
	SpriteFrame* image;
	MouseListener* listener;
	bool pointThis;
};
#endif