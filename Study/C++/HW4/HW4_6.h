#pragma once
class Circle
{
private:
	int radius;
	Circle* p;
public:
	void setRadius(int radius) { this->radius = radius; }
	double getArea() { return 3.14*radius*radius; }
};
