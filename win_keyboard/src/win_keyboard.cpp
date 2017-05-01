/***********************************************
* Zeus CMD - Win32 Tutorial 7 : Keyboard Input *
* By Grant James (ZEUS)                        *
* http://www.zeuscmd.com                       *
***********************************************/
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
						 WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE :
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY :
		PostQuitMessage(0);

	case WM_KEYDOWN :
		if (wParam == 'T')
			MessageBox(hwnd, "T Pressed", "T", MB_OK);
		else if (wParam == VK_ESCAPE)
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		break;

	case WM_KEYUP :
		if (wParam == 'R')
			MessageBox(hwnd, "R Pressed", "R", MB_OK);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nShowCmd)
{
	LPCTSTR className = "ClassName";
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Error registering class",
			"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	HWND hwnd = CreateWindowEx(
		0,
		className,
		"07 - Keyboard Input",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		300, 300,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hwnd)
	{
		MessageBox(NULL, "Error creating window",
			"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	ShowWindow(hwnd, nShowCmd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
