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

	SpriteFrame* getFrame(size_t index);
	void addSpriteFrame(SpriteFrame* frame);
	void addSpriteFrameByName(const GString& name);
	void setReplay(bool _replay);
	void setReset(bool _reset);
	void reset();
	inline size_t getFrameCount() const {
		return m_frameList.size();
	}

	SpriteFrame* nextFrame();
	SpriteFrame* preFrame();

protected:
	virtual void _update() override;
private:
	Vector<SpriteFrame*> m_frameList;
	size_t index;
	bool m_replay;
	bool m_reset;
};
#endif