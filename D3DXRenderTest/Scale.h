#ifndef __SCALE__
#define __SCALE__
#include "ActionInterval.h"

class ScaleTo: public ActionInterval{
public:
	static ScaleTo* create(float scale_x, float scale_y, long _time);

	virtual void init(Node* node) override;

	virtual void _update();

protected:
	Vec2 m_preScale;					//��һ�����ű���
	Vec2 m_dstScale;					//Ŀ�����ű���
	long m_remainTimer;					//ʣ��ִ��ʱ��
};

class ScaleBy: public ScaleTo{
public:
	static ScaleBy* create(float scale_x, float scale_y, long _time);
	virtual void init(Node* node) override;

private:

};
#endif