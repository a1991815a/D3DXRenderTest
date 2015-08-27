#ifndef __ANIMATE__
#define __ANIMATE__
#include "Ref.h"
#include "Vector.h"
#include "SpriteFrame.h"
#include "Sprite.h"
#include "Timer.h"
#include "ActionInterval.h"

class Animate: public ActionInterval{
public:
	static Animate* create();
	Animate();

	void addSpriteFrame(SpriteFrame* frame);
	void setReplay(bool _replay);
	void setReset(bool _reset);
	void reset();

protected:
	virtual void _update() override;
private:
	Vector<SpriteFrame*> m_frameList;
	size_t index;
	bool m_replay;
	bool m_reset;
};
#endif