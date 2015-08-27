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
	Vec2 m_prePosition;					//��һ��λ��
	Vec2 m_dstPosition;					//Ŀ��λ��
	time_type m_remainTimer;			//ʣ��ִ��ʱ��
};

class MoveBy: public MoveTo{
public:
	MoveBy();
	~MoveBy();
};

#endif