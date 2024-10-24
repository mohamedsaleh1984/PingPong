#include <iostream>
#include <Windows.h>
using namespace std;

bool isRunning = true;

struct RenderState {
	int width;
	int height;
	BITMAPINFO bufferBitmapInfo;
	int bufferSize;
	void* bufferMemory = nullptr;
};

RenderState _renderState;
 




LRESULT CALLBACK window_callback(HWND    hWnd, UINT    Msg, WPARAM  wParam, LPARAM  lParam)
{
	LRESULT result = 0;

	switch (Msg)
	{
	case WM_CLOSE:
	case WM_DESTROY: {
		// break the main window loop and exit the window.
		isRunning = false;

	}break;

	case WM_SIZE: {
		RECT rect;
		GetClientRect(hWnd, &rect);
		_renderState.width = rect.right - rect.left;
		_renderState.height = rect.bottom - rect.top;

		// number of pixels = w*h and each pixel is unsigned int
		_renderState.bufferSize = _renderState.width * _renderState.height * sizeof(unsigned int);

		//free if it's allocated...
		if (_renderState.bufferMemory) {
			VirtualFree(_renderState.bufferMemory, 0, MEM_RELEASE);
		}
		_renderState.bufferMemory = VirtualAlloc(0, _renderState.bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		_renderState.bufferBitmapInfo.bmiHeader.biSize = sizeof(_renderState.bufferBitmapInfo.bmiHeader);
		_renderState.bufferBitmapInfo.bmiHeader.biWidth = _renderState.width;
		_renderState.bufferBitmapInfo.bmiHeader.biHeight = _renderState.height;
		_renderState.bufferBitmapInfo.bmiHeader.biPlanes = 1;
		_renderState.bufferBitmapInfo.bmiHeader.biBitCount = 32;
		_renderState.bufferBitmapInfo.bmiHeader.biCompression = BI_RGB;

	}break;

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
	unsigned int styles = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	HWND windowHandle = CreateWindow(window_class.lpszClassName, L"My First Game", styles, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(windowHandle);

	// Main Windows Loop

	while (isRunning) {
		// Input
		MSG message;
		while (PeekMessage(&message, windowHandle, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		//  Simulate
		unsigned int* pixel = (unsigned int*)_renderState.bufferMemory;
		for (int y = 0; y < _renderState.height; ++y) {
			for (int x = 0; x < _renderState.width; ++x) {
				// Change the value of each pixel
				*pixel++ = x*y;
			}
		}
		//	Render
		StretchDIBits(hdc, 0, 0, 
			_renderState.width, 
			_renderState.height, 0, 0, 
			_renderState.width, 
			_renderState.height, 
			_renderState.bufferMemory, 
			&_renderState.bufferBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	}


	return 0;
};