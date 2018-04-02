#include "StdAfx.h"		
#include "MyShape.h"
#include "Resource.h"
#include "ChildView.h"

MyShape::MyShape(void)
{
}

MyShape::~MyShape(void)
{
}
void Pixel::DrawRgn(CDC* dc, Pixel pixel, int index, int count_pixel)
{

	CRgn rgn;
	rgn.CreatePolygonRgn(&(pixel.pixel[0]), count_pixel, ALTERNATE);
	CBrush brush(RGB(0, 0, 255));
	dc->SelectObject(&brush);
	dc->PaintRgn(&rgn);

}
void MyShape::Draw(CDC *pDC)
{

}
MyRect::MyRect(void)
{
}
MyRect::~MyRect(void)
{
}

void MyRect::Draw(CDC* dc)
{
	CBitmap bitmap;
	CDC dcMemory;
	bitmap.LoadBitmap(IDB_BITMAP1);
	BITMAP bmInfo;
	bitmap.GetObject(sizeof(bmInfo), &bmInfo);
	dcMemory.CreateCompatibleDC(dc);
	dcMemory.SelectObject(&bitmap);
	dc->StretchBlt(pstart.x, pstart.y,
		pend.x - pstart.x, pend.y - pstart.y,
		&dcMemory, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, SRCCOPY);
}
MyCircle::MyCircle(void)
{
}
MyCircle::~MyCircle(void)
{
}
void MyCircle::Draw(CDC* pdc)
{

	CBrush brush(RGB(254, 254, 65));
	CBrush* pOldBrush = pdc->SelectObject(&brush);
	pdc->Ellipse(CRect(pstart, pend));
	pdc->SelectObject(pOldBrush);
}