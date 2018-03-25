/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #1_4
Visual Studio 2015
*/

#include"W1_4.h"
MyShape::MyShape() 
{ 
	x = 0; y = 0; 
}
MyShape::MyShape(int ix, int iy)
{
	x = ix;
	y = iy;
}
void MyShape::draw()
{
	cout << "[MyShape]" << "(" << x << "," << y << ")" << endl;
}
MyRect::MyRect() 
{ 
	w = 0; h = 0; 
}
MyRect::MyRect(int ix, int iy, int iw, int ih):MyShape(ix,iy)
{
	x = ix;
	y = iy;
	w = iw;
	h = ih;
}
void MyRect::draw()
{
	cout << "[MyRect]" << "(" << x << "," << y << ")" << "w:" << w << "h:" << h << endl;
}
MyCircle::MyCircle()
{
	r = 0;
}
MyCircle::MyCircle(int ix, int iy, int ir):MyShape(ix,iy)
{
	x = ix;
	y = iy;
	r = ir;
}
void MyCircle::draw()
{
	cout << "[MyCircle]" << "(" << x << "," << y << ")" << "r:" << r << endl;
}

int main()
{
	MyShape* pShape1 = new MyShape(10, 3);
	MyShape* pShape2 = new MyRect(3, 5, 7, 8);
	MyShape* pShape3 = new MyCircle(4, 5, 1);

	pShape1->draw();
	pShape2->draw();
	pShape3->draw();

	delete pShape1;
	delete pShape2;
	delete pShape3;

	return 0;
}