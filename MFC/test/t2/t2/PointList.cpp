#include "stdafx.h"
#include "PointList.h"


PointList::PointList()
{
	orip.x = 0; orip.y = 0;
	endp.x = 0; endp.y = 0;
}


PointList::~PointList()
{
}
void PointList::draw(CDC* pdc)
{
	CBrush*old=pdc->SelectObject(&brush);
	pdc->Rectangle(CRect(orip, endp));
	brush.DeleteObject();							//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ÒªÉ¾³ý»­Ë¢
	pdc->SelectObject(old);
}
