/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #10_5
Visual Studio 2015
*/
#include<iostream>
using namespace std;
template<typename T>
T* concat(T* a, int sizea, T* b, int sizeb)
{
	T* add = new T[sizea + sizeb+1];
	T* tail = add;
	while (sizea > 0)
	{
		*tail++ = *a++;
		sizea--;
	}
	while (sizeb > 0)
	{
		*tail++ = *b++;
		sizeb--;
	}
	return add;
}
int main()
{
	int c[] = { 1,2,3 };
	int f[] = { 4,5,6,7 };
	int *add = concat(c, 3, f, 4);
	for (int j = 0; j < 7; j++)
	{
		cout << add[j]<<' ';
	}
	delete add;
	return 0;
}