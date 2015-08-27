#ifndef __WIN32UTILS__
#define __WIN32UTILS__
#include <windows.h>
#include "UtilsHeader.h"

class Win32Utils{
public:
	static Win32Utils* getInstance();
	static void destroyInstance();
private:
	static Win32Utils* m_instance;

private:
	HWND m_hWnd;
public:
	HWND createWindow(const GString& wnd_name, int width, int height);
	void destroyWindow();
	inline HWND getWin32Window() const { return m_hWnd; };
	int getWidth() const{return m_width;};
	int getHeight() const{return m_height;};
private:
	Win32Utils();
	~Win32Utils();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	int m_width;
	int m_height;
};
#endif