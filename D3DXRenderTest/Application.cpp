#include "Application.h"
#include "GBAssert.h"

bool Application::init()
{
	m_frame = 1000 / 60;
	{
		auto itor = m_gameInnerLoop.begin();
		for (; itor != m_gameInnerLoop.end(); ++itor)
		{
			bool result = (*itor)->init();
			GBASSERT(result);
		}
	}

	{
		auto itor = m_gameExternLoop.begin();
		for (; itor != m_gameExternLoop.end(); ++itor)
		{
			bool result = (*itor)->init();
			GBASSERT(result);
		}
	}
	render_engine->init();
	return true;
}

void Application::loop()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)){
			::TranslateMessage(&msg);
			::DispatchMessageA(&msg);
		}
		else if(m_globalTimer.getDelta() > m_frame)
		{
			auto itor = m_gameInnerLoop.begin();
			for (; itor != m_gameInnerLoop.end(); ++itor)
				(*itor)->loop();
			render_engine->loop();
			m_globalTimer.reset();
		}
		else
			Sleep(1);
		auto itor = m_gameExternLoop.begin();
		for (; itor != m_gameExternLoop.end(); ++itor)
			(*itor)->loop();
	}
}

void Application::destroy()
{
	auto itor = m_gameInnerLoop.rbegin();
	for (; itor != m_gameInnerLoop.rend(); ++itor)
		(*itor)->destroy();
}
