#include "Application.h"
#include "GBAssert.h"

bool Application::init()
{
	auto itor = m_gameStepList.begin();
	for (; itor != m_gameStepList.end(); ++itor)
	{
		bool result = (*itor)->init();
		GBASSERT(result);
	}
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
		else
		{
			auto itor = m_gameStepList.begin();
			for (; itor != m_gameStepList.end(); ++itor)
				(*itor)->loop();
			Sleep(1);
		}
	}
}

void Application::destroy()
{
	auto itor = m_gameStepList.rbegin();
	for (; itor != m_gameStepList.rend(); ++itor)
		(*itor)->destroy();
}
