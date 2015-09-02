#include "Actor.h"

Actor::Actor()
	:m_body(nullptr),
	m_runAnimate(nullptr), m_attackAnimate(nullptr)
{

}

void Actor::visit()
{
	m_body->visit();
}

void Actor::Run(long direction, void* data /*= nullptr*/)
{
	switch (direction)
	{
	case DIRECTION_LEFT:
		if (!getClip())
			setClip(true);
		m_body->runAction(m_runAnimate);
		break;
	case DIRECTION_RIGHT:
		if (getClip())
			setClip(false);
		m_body->runAction(m_runAnimate);
		break;
	default:
		GBASSERT(false);
	}
}

void Actor::Attack(long direction, void* data /*= nullptr*/)
{

	switch (direction)
	{
	case ATTACK_LEFT:
		m_body->runAction(m_attackAnimate);						//需要翻转接口
		break;
	case ATTACK_RIGHT:
		m_body->runAction(m_attackAnimate);
		break;
	default:
		GBASSERT(false);
	}
}
