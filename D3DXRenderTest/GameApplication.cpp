#include "GameApplication.h"
#include "Win32Utils.h"
#include "MacroHeader.h"

bool GameApplication::init()
{
	Win32Utils::getInstance()->createWindow("�ҵĲ��Դ���", 800, 600);
	return Application::init();
}
