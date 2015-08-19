#include "Application.h"
#include "GBAssert.h"
#include "Win32Utils.h"
#include "SingleInstance.h"
#include "TimerManager.h"
#include "Director.h"
#include "MacroHeader.h"

bool Application::init()
{
	_director->m_app = this;
	setResignSize(WINNAME, WND_WIDTH, WND_HEIGHT, REFRESH_FRAME);
	Win32Utils::getInstance()->createWindow(
		m_wndName.c_str(), m_wndSize.x, m_wndSize.y);
	m_delay = (float)1000 / (float)m_frame;
	return true;
}

int Application::run()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)){
			::TranslateMessage(&msg);
			::DispatchMessageA(&msg);
		}
		else if(m_globalTimer.getDelta() > m_delay)				//Ö÷Ñ­»·
		{
			_director->loop();
			m_globalTimer.reset();
		}
		else
			Sleep(1);
		TimerManager::getInstance()->loop();
	}
	return msg.wParam;
}

void Application::destroy()
{
	_director->destroy();
}
