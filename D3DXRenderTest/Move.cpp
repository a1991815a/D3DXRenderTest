#include "MoveBy.h"

void MoveTo::_update()
{
	Vec2 moveVector = m_dstPosition - m_prePosition;
	moveVector *= (float)getDelta() / (float) m_remainTimer;
	m_prePosition = getNode()->getPosition() + moveVector;
	getNode()->setPosition(m_prePosition);
	m_remainTimer -= getDelta();
	if (m_remainTimer <= 0)
		setStop();
}

MoveBy::MoveBy()
{

}

MoveBy::~MoveBy()
{

}
