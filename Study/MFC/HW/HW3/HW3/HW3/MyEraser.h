#pragma once
#include "Line.h"
class MyEraser
{
private:
	CPoint sp, ep;
public:
	MyEraser();
	~MyEraser();
	void setPosition(CPoint, CPoint);
	CRect getPositon();
	void movePositon(int, int);
	void doErase(CDC*,Line&);
	void delEraser();
};

