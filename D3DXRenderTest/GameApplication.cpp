#include "GameApplication.h"
#include "Win32Utils.h"
#include "MacroHeader.h"

void GameApplication::init()
{
	Win32Utils::getInstance()->createWindow(WINNAME, WND_WIDTH, WND_HEIGHT);
}

int GameApplication::run()
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
			getRenderEngine()->render();
			Sleep(1);
		}
	}
	return msg.wParam;
}

void GameApplication::destroy()
{
	
}
