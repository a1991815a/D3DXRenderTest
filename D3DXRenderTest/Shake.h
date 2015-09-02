#ifndef __SHAKE__
#define __SHAKE__
#include "ActionInterval.h"

class Shake: public ActionInterval{
public:
	static Shake* create(int offset, float delay, float time_count);

	virtual void init(Node* node) override;

	virtual void _update();


private:
	int m_offset;
	float m_timeCount;
	Vec2 m_resetPosition;
	bool m_isReset;
};
#endif