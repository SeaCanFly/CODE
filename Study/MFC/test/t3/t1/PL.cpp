#include "stdafx.h"
#include "PL.h"


PL::PL()
{
}


PL::~PL()
{
}
void PL::draw(CDC* pdc)
{
	pdc->Rectangle(CRect(spos, epos));
}
void PL::color(CDC* pdc)
{
	CBrush brush(RGB(255,0,0));
	pdc->SelectObject(&brush);
	pdc->Rectangle(CRect(spos, epos));
}