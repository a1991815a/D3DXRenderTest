#ifndef __MOVE__
#define __MOVE__
#include "ActionInterval.h"
#include "Vec.h"

class MoveTo: public ActionInterval{
public:
	MoveTo();
	~MoveTo();

protected:
	virtual void _update();
private:
	Vec2 m_prePosition;					//上一次位置
	Vec2 m_dstPosition;					//目标位置
	time_type m_remainTimer;			//剩余执行时间
};

class MoveBy: public MoveTo{
public:
	MoveBy();
	~MoveBy();
};

#endif