#pragma once
#include"shape.h"
void Shape::fdraw(HWND hwnd,HDC hdc)
{	
	char str[1000] = { 0 };
	sprintf(str, "[Shape]=Pos(%.3f,%.3f)\n", x, y);
	SetPixel(hdc, x, y, RGB(255, 0, 0));
	MessageBox(0, str, "Shape", 0);
}
