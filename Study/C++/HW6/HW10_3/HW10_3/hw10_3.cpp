/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #10_3
Visual Studio 2015
*/
#include<iostream>
using namespace std;
template<typename T>
void reverseArray(T* a, int n)
{
	for (int i = 0; i < n/2; i++)
	{
		T temp = a[i];
		a[i] = a[n - i - 1];
		a[n - i - 1] = temp;
	}
}
int main()
{
	int x[] = { 1,10,100,5,4 };
	reverseArray(x, 5);
	for (int i = 0; i < 5; i++)
	{
		cout << x[i] << ' ';
	}
	cout << endl;
	return 0;
}