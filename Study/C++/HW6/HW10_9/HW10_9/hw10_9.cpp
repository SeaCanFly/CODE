/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #10_9
Visual Studio 2015
*/
#include<iostream>
#include<vector>
using namespace std;
double average(vector<int>& v)
{
	double sum = 0.0;
	for (int i = 0; i < v.size(); i++)
	{
		sum += v[i];
	}
	return sum / v.size();
}
void show(vector<int>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout<<v[i]<<' ';
	}
	cout << endl;
}
int main()
{
	vector<int>v;
	while (1)
	{
		int num = 0,sum=0;
		cout << "Input an integer(Enter 0 to exit)>>";
		cin >> num;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cin >> num;
		}
		if (num == 0)
		{
			break;
		}
		v.push_back(num);
		show(v);
		cout << "average:" << average(v) << endl;
	}
	return 0;
}