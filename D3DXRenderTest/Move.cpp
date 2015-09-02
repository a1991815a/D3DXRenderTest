#include "Move.h"

MoveTo* MoveTo::create(float x, float y, long _time)
{
	MoveTo* ret = nullptr;
	gbAlloc(ret);
	ret->m_dstPosition.x = x;
	ret->m_dstPosition.y = y;
	ret->m_remainTimer = _time;

	ret->autorelease();
	return ret;
}

MoveTo::MoveTo()
	:m_remainTimer(0)
{

}

MoveTo::~MoveTo()
{

}

void MoveTo::_update()
{
	if (m_remainTimer <= 0)
		setStop(true);
	Vec2 moveVector = m_dstPosition - m_prePosition;
	moveVector *= (float)getDelta() / (float) m_remainTimer;
	m_prePosition = getNode()->getPosition() + moveVector;
	getNode()->setPosition(m_prePosition);
	m_remainTimer -= getDelta();
	if (m_remainTimer <= 0)
		getNode()->setPosition(m_dstPosition);
}

void MoveTo::init(Node* node)
{
	ActionInterval::init(node);
	m_prePosition = node->getPosition();;
}

MoveBy* MoveBy::create(float x, float y, long _time)
{
	MoveBy* ret = nullptr;
	gbAlloc(ret);
	ret->m_dstPosition.x = x;
	ret->m_dstPosition.y = y;
	ret->m_remainTimer = _time;

	ret->autorelease();
	return ret;
}

MoveBy::MoveBy()
{

}

MoveBy::~MoveBy()
{

}

void MoveBy::init(Node* node)
{
	MoveTo::init(node);
	m_dstPosition = m_prePosition + m_dstPosition;
}
