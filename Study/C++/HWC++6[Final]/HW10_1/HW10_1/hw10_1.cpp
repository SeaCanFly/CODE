/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #10_1
Visual Studio 2015
*/
#include<iostream>
using namespace std;
template<typename T>
T biggest(T* a, int b)
{
	T temp = *a;
	for (int i = 0; i < b; i++)
	{
		if (temp < a[i])
		{
			temp = a[i];
		}
	}
	return temp;
}
int main()
{
	int x[] = { 1,10,100,5,4 };
	cout << biggest(x, 5) << endl;
	return 0;
}