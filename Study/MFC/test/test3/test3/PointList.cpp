#include "stdafx.h"
#include "PointList.h"


PointList::PointList()
{
}


PointList::~PointList()
{
}
void PointList::draw(CDC* pdc)
{
	CBrush* old_brush=pdc->SelectObject(&brush);
	pdc->Rectangle(CRect(startp, endp));
	brush.DeleteObject();
	pdc->SelectObject(old_brush);
}