/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #8_5
Visual Studio 2015
*/
#include"hw8_5.h"
#include<iostream>
using namespace std;
int main()
{
	MyQueue mQ(100);
	int n;
	cout << "Input 5 integers>>";
	for (int i = 0; i < 5; i++)
	{
		cin >> n;
		mQ.fEnqueue(n);
	}
	cout << "Capacity:" << mQ.fCapacity() << ", size of the queue:" << mQ.fLength() << endl;
	cout << "Deleted:";
	while (mQ.fLength() != 0)
	{
		cout << mQ.fDequeue() << ' ';
	}
	cout << endl << "the size of the queue:" << mQ.fLength() << endl;
	return 0;
}