#include "ActionInterval.h"

ActionInterval::ActionInterval()
	:Action(Action::ACTION_INTERVAL),
	m_timer(),
	m_delay(0)
{
	m_timer.setPause(true);
}

ActionInterval::~ActionInterval()
{
}

void ActionInterval::setDelay(time_type delay)
{
	m_delay = delay;
}

time_type ActionInterval::getDelay() const
{
	return m_delay;
}

void ActionInterval::update()
{
	GBASSERT(isInit);
	if(m_timer.getDelta() >= m_delay)
	{
		this->_update();
		m_timer.reset();
	}
}

void ActionInterval::setPause( bool pause )
{
	m_timer.setPause(pause);
}

bool ActionInterval::getPause() const
{
	return m_timer.getPause();
}

time_type ActionInterval::getDelta() const
{
	return m_timer.getDelta();
}

void ActionInterval::init(Node* node)
{
	Action::init(node);
	isInit = true;
	m_timer.reset();
	m_timer.setPause(false);
}
