#pragma once



class MyShape
{
public:
	MyShape(void);

	~MyShape(void);

	CPoint pstart;
	CPoint pend;

	virtual void Draw(CDC*);
};
class Pixel
{
public:
	CPoint pixel[100];
	Pixel() {};
	~Pixel() {};
	void DrawRgn(CDC*, Pixel, int, int);
};
class MyRect :public MyShape
{
public:
	MyRect(void);

	~MyRect(void);
	void Draw(CDC*);
};

class MyCircle :public MyShape
{
public:
	MyCircle();
	~MyCircle();
	void Draw(CDC*);
};