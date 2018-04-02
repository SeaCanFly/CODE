/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #10_13
Visual Studio 2015
*/
#include"hw10_13.h"
void searchToDelete(vector<Circle>& v, string name)
{
	vector<Circle>::iterator it;
	for (it=v.begin();it!=v.end();)
	{
		if (it->getName()==name)
		{
			it = v.erase(it);		
		}
		else
		{
			it++;
		}
	}
}
void show(vector<Circle>& v)
{
	vector<Circle>::iterator it;
	for (it = v.begin(); it != v.end();)
	{
		cout << it->getName()<<endl;
		it++;
	}
}
int main()
{
	vector<Circle>v;
	cout << "Add circle and delete circle." << endl;
	while (1)
	{
		string name = "";
		int radius = 0;
		string select = "";
		cout << "Add:1, Delete:2, Look:3, Exit:4>>";
		cin >> select;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cin >> select;
		}
		if (select == "4")
		{
			break;
		}
		if (select == "1")
		{
			cout << "Input the radius and name>>";
			cin >> radius >> name;
			Circle temp(radius, name);
			v.push_back(temp);
		}
		if (select == "2")
		{
			cout << "Enter the name you want to delete>>";
			cin >> name;
			searchToDelete(v, name);
		}
		if (select == "3")
		{
			show(v);
		}
	}
	return 0;
}