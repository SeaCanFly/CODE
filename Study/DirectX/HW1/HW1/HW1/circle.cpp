#pragma once
#include "circle.h"
void Circle::fdraw(HWND hwnd,HDC hdc)
{
	char str[1000] = { 0 };
	sprintf(str, "[Circle]=Pos(%.2f,%.2f),Radius=%.2f)\n", x, y, r);
	Ellipse(hdc, x - r, y + r, x + r, y - r);
	MessageBox(0, str, "Circle", 0);
}
