#include"shape.h"
#include"rect.h"
#include"circle.h"
LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "MyWndClass";
	RegisterClass(&wc);
	hwnd = CreateWindow(
		"MyWndClass", // WNDCLASS name
		"SDK Application", // Window title
		WS_OVERLAPPEDWINDOW, // Window style
		CW_USEDEFAULT, // Horizontal position
		CW_USEDEFAULT, // Vertical position
		CW_USEDEFAULT, // Initial width
		CW_USEDEFAULT, // Initial height
		HWND_DESKTOP, // Handle of parent window
		NULL, // Menu handle
		hInstance, // Application's instance handle
		NULL // Window-creation data
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);	
		RECT rect;
		GetClientRect(hwnd, &rect);
		DrawText(hdc, "hello, Windows", -1, &rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		RECT rect;
		GetClientRect(hwnd, &rect);
		Shape* pt[3] = { nullptr };
		pt[0] = new Shape(rect.right/2, rect.bottom/2);
		pt[1] = new Rect(rect.left+100, rect.top+100, rect.right-100, rect.bottom-100);
		pt[2] = new Circle(rect.right/2, rect.bottom/2, rect.bottom/2-200);
		hdc = GetDC(hwnd);
		for (int i = 0; i < 3; i++)
		{
			pt[i]->fdraw(hwnd,hdc);
		}
		ReleaseDC(hwnd, hdc);
		for (int i = 0; i < 3; i++)
		{
			delete pt[i];
			pt[i] = nullptr;
		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}