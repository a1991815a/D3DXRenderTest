#include "Scale.h"

ScaleTo* ScaleTo::create(float scale_x, float scale_y, long _time)
{
	ScaleTo* ret = nullptr;
	gbAlloc(ret);
	ret->m_dstScale.x = scale_x;
	ret->m_dstScale.y = scale_y;
	ret->m_remainTimer = _time;

	ret->autorelease();
	return ret;
}

void ScaleTo::init(Node* node)
{
	ActionInterval::init(node);
	m_preScale = node->getScale();
}

void ScaleTo::_update()
{
	if (m_remainTimer <= 0)
		setStop(true);
	Vec2 scaleVector = m_dstScale - m_preScale;
	scaleVector *= (float)getDelta() / (float) m_remainTimer;
	m_preScale = getNode()->getScale() + scaleVector;
	getNode()->setScale(m_preScale);
	m_remainTimer -= getDelta();
	if (m_remainTimer <= 0)
		getNode()->setScale(m_dstScale);
}

ScaleBy* ScaleBy::create(float scale_x, float scale_y, long _time)
{
	ScaleBy* ret = nullptr;
	gbAlloc(ret);
	ret->m_dstScale.x = scale_x;
	ret->m_dstScale.y = scale_y;
	ret->m_remainTimer = _time;
	ret->autorelease();
	return ret;
}

void ScaleBy::init(Node* node)
{
	ScaleTo::init(node);
	m_dstScale = m_preScale + m_dstScale;
}
