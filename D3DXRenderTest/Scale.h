#ifndef __SCALE__
#define __SCALE__
#include "ActionInterval.h"

class ScaleTo: public ActionInterval{
public:
	static ScaleTo* create(float scale_x, float scale_y, long _time);

	virtual void init(Node* node) override;

	virtual void _update();

protected:
	Vec2 m_preScale;					//上一次缩放比例
	Vec2 m_dstScale;					//目标缩放比例
	long m_remainTimer;					//剩余执行时间
};

class ScaleBy: public ScaleTo{
public:
	static ScaleBy* create(float scale_x, float scale_y, long _time);
	virtual void init(Node* node) override;

private:

};
#endif