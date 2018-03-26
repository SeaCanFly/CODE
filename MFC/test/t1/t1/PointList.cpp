#include "stdafx.h"
#include "PointList.h"


PointList::PointList()
{
}


PointList::~PointList()
{
}
void PointList::drawSavePoint(CDC* pdc,CPoint pt)
{
	pdc->SetPixel(pt, RGB(0, 0, 255));
	plist.AddHead(pt);
}
void PointList::drawPoint(CDC* pdc, CPoint pt)
{
	pdc->SetPixelV(pt, RGB(0, 0, 255));
}
void PointList::cleenPoint(CPoint sp, CPoint ep)
{
	int num = plist.GetCount();
	for (int i = 0; i < num; i++)
	{
		POSITION pos = plist.FindIndex(i);
		CPoint temp = plist.GetAt(pos);

		if ((temp.x - sp.x)*(temp.x - ep.x) < 0 && (temp.y - sp.y)*(temp.y - ep.y) < 0)
		{
			plist.RemoveAt(pos);
			num--;
			i--;  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ɾ��һ���ڵ㣬����ĻᲹ���ȥ������iҲҪ��ȥһ��
		}
	}
}