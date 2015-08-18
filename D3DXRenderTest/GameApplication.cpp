#include "GameApplication.h"
#include "Win32Utils.h"
#include "MacroHeader.h"

bool GameApplication::init()
{
	Win32Utils::getInstance()->createWindow(WINNAME, WND_WIDTH, WND_HEIGHT);
	return Application::init();
}
