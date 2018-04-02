#pragma once
class MyEllipse
{
public:
	MyEllipse();
	~MyEllipse();
	CPoint startp, endp;
	int v;
	void draw(CDC*);
};

