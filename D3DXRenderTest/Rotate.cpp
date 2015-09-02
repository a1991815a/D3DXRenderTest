#include "Rotate.h"

RotateTo* RotateTo::create(float rotate_x, float rotate_y, float rotate_z, long _time)
{
	RotateTo* ret = nullptr;
	gbAlloc(ret);
	ret->m_dstRotate.x = rotate_x;
	ret->m_dstRotate.y = rotate_y;
	ret->m_dstRotate.z = rotate_z;
	ret->m_remainTimer = _time;
	ret->autorelease();
	return ret;
}

void RotateTo::init(Node* node)
{
	ActionInterval::init(node);
	m_preRotate = node->getRotate();
}

void RotateTo::_update()
{
	if (m_remainTimer <= 0)
		setStop(true);
	Vec3 scaleVector = m_dstRotate - m_preRotate;
	scaleVector *= (float)getDelta() / (float) m_remainTimer;
	m_preRotate = getNode()->getRotate() + scaleVector;

	getNode()->setRotate(m_preRotate);
	m_remainTimer -= getDelta();
	if (m_remainTimer <= 0)
		getNode()->setRotate(m_dstRotate);
}

RotateBy* RotateBy::create(float rotate_x, float rotate_y, float rotate_z, long _time)
{
	RotateBy* ret = nullptr;
	gbAlloc(ret);
	ret->m_dstRotate.x = rotate_x;
	ret->m_dstRotate.y = rotate_y;
	ret->m_dstRotate.z = rotate_z;
	ret->m_remainTimer = _time;
	ret->autorelease();
	return ret;
}

void RotateBy::init(Node* node)
{
	RotateTo::init(node);
	m_dstRotate = m_preRotate + m_dstRotate;
}
