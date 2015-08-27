#include "ActionInterval.h"

void ActionInterval::setDelay( time_type delay )
{
	m_delay = delay;
}

time_type ActionInterval::getDelay() const
{
	return m_delay;
}

void ActionInterval::update()
{
	if(m_delay >= m_timer.getDelta())
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
