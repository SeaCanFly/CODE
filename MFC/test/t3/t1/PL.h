#pragma once
class PL
{
public:
	PL();
	~PL();
	CPoint spos;
	CPoint epos;
	void draw(CDC*);
	void color(CDC*);
};

