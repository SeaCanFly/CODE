#include "stdafx.h"
#include "MyEraser.h"


MyEraser::MyEraser()
{
}


MyEraser::~MyEraser()
{
}
void MyEraser::setPosition(CPoint startp, CPoint endp)
{
	sp = startp; ep = endp;
}
CRect MyEraser::getPositon()
{
	return CRect(sp, ep);
}
void MyEraser::delEraser()
{
	sp.x = 0; sp.y = 0;
	ep.x = 0; ep.y = 0;
	setPosition(sp,ep);
}
void MyEraser::movePositon(int x, int y)
{
	sp.x += x;
	sp.y += y;
	ep.x += x;
	ep.y += y;
}
void MyEraser::doErase(CDC* pdc, Line& line)
{
	CPen pen(PS_SOLID, 1, RGB(128, 0, 128));
	pdc->SelectObject(&pen);
	pdc->Rectangle(CRect(sp, ep));
	POSITION pos = line.getLine().GetHeadPosition();
	while (pos != 0)
	{
		POSITION dpos = pos;
		CPoint ptemp = line.getMyPoint(pos).getPoint();
		CRect rect = getPositon();
		line.getLine().GetNext(pos);
		if ((ptemp.x-sp.x)*(ptemp.x-ep.x)<=0&&(ptemp.y-sp.y)*(ptemp.y-ep.y)<=0)
		{
			line.delMyPoint(dpos);
		}
	}
}