#pragma once
#include "rect.h"
void Rect::fdraw(HWND hwnd,HDC hdc)
{
	char str[1000] = { 0 };
	sprintf(str, "[Rect]=Pos(%.2f,%.2f),Size(%.2f,%.2f)\n", x, y, w, h);
	Rectangle(hdc, x, y, w, h);
	MessageBox(0, str, "Rect", 0);
}
