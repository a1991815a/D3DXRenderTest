#include "Shake.h"
#include <windows.h>

Shake* Shake::create(int offset, float delay, float time_count)
{
	Shake* ret = nullptr;
	gbAlloc(ret);
	ret->autorelease();
	ret->m_offset = offset;
	ret->setDelay(delay);
	ret->m_timeCount = time_count;
	ret->m_isReset = true;

	return ret;
}

void Shake::init(Node* node)
{
	ActionInterval::init(node);
	m_resetPosition = getNode()->getPosition();
}

void Shake::_update()
{
	if((m_timeCount -= getDelta()) <= 0)
	{
		getNode()->setPosition(m_resetPosition);
		setStop(true);
	}
	if(!m_isReset)
	{
		getNode()->setPosition(m_resetPosition);
		m_isReset = true;
		return;
	}


	srand(GetTickCount() + 1);
	int num = rand();
	float offset_x = 0;
	float offset_y = 0;
	if(num % 2 == 0)
		offset_x = num % m_offset;
	else
		offset_x = - (num % m_offset);

	srand(GetTickCount() + 2);
	num = rand();
	if(num % 2 == 0)
		offset_y = num % m_offset;
	else
		offset_y = - (num % m_offset);
	getNode()->setPositionX(getNode()->getPosition().x + offset_x);
	getNode()->setPositionY(getNode()->getPosition().y + offset_y);
	m_isReset = false;
}
