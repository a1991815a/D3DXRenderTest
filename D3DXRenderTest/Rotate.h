#ifndef __ROTATE__
#define __ROTATE__
#include "ActionInterval.h"
#include "Vec.h"

class RotateTo: public ActionInterval{
public:
	static RotateTo* create(
		float rotate_x, 
		float rotate_y, 
		float rotate_z, 
		long _time);

protected:
	virtual void init(Node* node) override;
	virtual void _update();

protected:
	Vec3 m_preRotate;
	Vec3 m_dstRotate;
	long m_remainTimer;
};

class RotateBy: public RotateTo{
public:
	static RotateBy* create(
		float rotate_x, 
		float rotate_y, 
		float rotate_z, 
		long _time);
private:
	virtual void init(Node* node) override;
};
#endif