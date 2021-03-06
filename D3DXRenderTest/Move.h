#ifndef __MOVE__
#define __MOVE__
#include "ActionInterval.h"
#include "Vec.h"

class MoveTo: public ActionInterval{
	friend class MoveBy;
public:
	static MoveTo* create(float x, float y, long _time);
public:
	MoveTo();
	~MoveTo();

protected:
	virtual void _update();

	virtual void init(Node* node) override;

private:
	Vec2 m_prePosition;					//上一次位置
	Vec2 m_dstPosition;					//目标位置
	long m_remainTimer;					//剩余执行时间
};

class MoveBy: public MoveTo{
public:
	static MoveBy* create(float x, float y, long _time);


public:
	MoveBy();
	~MoveBy();

	virtual void init(Node* node) override;


private:

};

#endif