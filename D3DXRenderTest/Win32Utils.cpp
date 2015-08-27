#include "Win32Utils.h"
#include "GBAssert.h"
#include "MessageManager.h"

extern bool GameInit(HWND hWnd);

Win32Utils* Win32Utils::m_instance = nullptr;

static int client_width = 0;
static int client_height = 0;


Win32Utils::Win32Utils()
	:m_hWnd(nullptr), m_width(0), m_height(0)
{

}

Win32Utils::~Win32Utils()
{
	if (m_hWnd)
	{
		destroyWindow();
		m_hWnd = nullptr;
	}
}

Win32Utils* Win32Utils::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new Win32Utils();
	return m_instance;
}

void Win32Utils::destroyInstance()
{
	if (m_instance) {
		delete m_instance;
		m_instance = nullptr;
	}
}

HWND Win32Utils::createWindow(const GString& wnd_name, int width, int height)
{
	m_width = width;
	m_height = height;
	GBASSERT(m_hWnd == nullptr);
	WNDCLASSEXA wnd_class = { 0 };
	wnd_class.cbSize = sizeof(wnd_class);
	wnd_class.hInstance = GetModuleHandleA(nullptr);
	wnd_class.lpfnWndProc = Win32Utils::WndProc;
	wnd_class.lpszClassName = wnd_name.c_str();
	wnd_class.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;

	::RegisterClassExA(&wnd_class);

	m_hWnd = ::CreateWindowExA(
		0,
		wnd_name.c_str(),
		wnd_name.c_str(),
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		nullptr,
		nullptr,
		GetModuleHandleA(nullptr),
		nullptr
		);
	GBASSERT(m_hWnd != nullptr);
	
	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	::UpdateWindow(m_hWnd);

	return m_hWnd;
}

void Win32Utils::destroyWindow()
{
	if (m_hWnd)
		::DestroyWindow(m_hWnd);
}

LRESULT CALLBACK Win32Utils::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		{
			RECT rect;
			::GetClientRect(hwnd, &rect);
			client_width = rect.right - rect.left;
			client_height = rect.bottom - rect.top;
		}
		if (!GameInit(hwnd))
			PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		_dispatchMessage->sendKeyMessage((char)wParam, ET_KEY_DOWN);
		break;
	case WM_KEYUP:
		_dispatchMessage->sendKeyMessage((char)wParam, ET_KEY_UP);
		break;
	case WM_LBUTTONDOWN:
		_dispatchMessage->sendMouseMessage(
			(float)LOWORD(lParam), 
			client_height - (float)HIWORD(lParam), 
		   ET_MOUSE_LDOWN);
		break;
	case WM_LBUTTONUP:
		_dispatchMessage->sendMouseMessage(
			(float)LOWORD(lParam), 
			client_height - (float)HIWORD(lParam),
		   ET_MOUSE_LUP);
		break;
	case WM_MOUSEMOVE:
		_dispatchMessage->sendMouseMessage(
			(float)LOWORD(lParam), 
			client_height - (float)HIWORD(lParam), 
			ET_MOUSE_MOVE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcA(hwnd, message, wParam, lParam);
	}

	return 0;
}

