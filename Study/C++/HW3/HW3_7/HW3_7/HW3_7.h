#pragma once
class Oval
{
private:
	int width, height;
public:
	Oval();
	Oval(int, int);
	~Oval();
	void show();
	void set(int, int);
	int getWidth();
	int getHeight();
};
