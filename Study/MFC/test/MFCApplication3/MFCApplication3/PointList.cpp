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
	CBrush* oldb = pdc->SelectObject(&brush);
	pdc->Rectangle(CRect(sp, ep));
	brush.DeleteObject();
	pdc->SelectObject(oldb);
}