#include "stdafx.h"
#include "PointList.h"


PointList::PointList()
{
	startp.x = 0; startp.y = 0;
	endp.x = 0; endp.y = 0;
}


PointList::~PointList()
{
}
void PointList::draw(CDC* pdc)
{
	CBrush* old_brush = pdc->SelectObject(&brush);
	pdc->Rectangle(CRect(startp, endp));
	brush.DeleteObject();
	pdc->SelectObject(old_brush);
}
