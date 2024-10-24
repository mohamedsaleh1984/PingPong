#include <iostream>
#include <Windows.h>
using namespace std;

bool isRunning = true;

LRESULT CALLBACK window_callback(HWND    hWnd, UINT    Msg, WPARAM  wParam, LPARAM  lParam)
{
	LRESULT result = 0;
	switch (Msg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		// break the main window loop and exit the window.
		isRunning = false;
		break;

	default:
		result = DefWindowProc(hWnd, Msg, wParam, lParam);
		break;
	}
	return result;
}

int  WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR     lpCmdLine, int       nShowCmd)
{
	// Window class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Widnow";
	window_class.lpfnWndProc = window_callback;

	// Register class
	RegisterClass(&window_class);

	// Create window
	HWND windowHandle = CreateWindow(
		window_class.lpszClassName,
		L"My First Game",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1280, 720, 0, 0, hInstance, 0);

	// Windows Loop

	while (isRunning) {
		// Input
		MSG message;
		while (PeekMessage(&message, windowHandle, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		//  Simulate

		//	Render
	}


	return 0;
}