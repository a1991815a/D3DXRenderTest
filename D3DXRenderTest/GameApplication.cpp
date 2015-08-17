#include "GameApplication.h"
#include "Win32Utils.h"
#include "MacroHeader.h"

bool GameApplication::init()
{
	Win32Utils::getInstance()->createWindow("ÎÒµÄ²âÊÔ´°¿Ú", 800, 600);
	return Application::init();
}
