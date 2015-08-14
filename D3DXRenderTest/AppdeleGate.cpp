#include "AppdeleGate.h"

AppdeleGate* AppdeleGate::m_instance = nullptr;

AppdeleGate* AppdeleGate::getInstance()
{
	if(m_instance == nullptr)
		m_instance = new AppdeleGate();
	return m_instance;
}

void AppdeleGate::destroyInstance()
{
	if(m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

AppdeleGate::AppdeleGate()
	:m_app(nullptr)
{}

AppdeleGate::~AppdeleGate()
{
	m_app->_destroy();
}

void AppdeleGate::init()
{
	m_app->_init();
}
