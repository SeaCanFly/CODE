/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #1_1
Visual Studio 2015
*/

#include"W1_1.h"
CStudent::CStudent() 
{
	name = ""; id = ""; major = ""; grade = "";
}
CStudent::CStudent(string n, string i, string m, string g)
{
	name = n;
	id = i;
	major = m;
	grade = g;
};
void CStudent::ShowData()
{
	cout << "Name:" << name << "\t" << "Id:" << id << "\t" << "Major:" << major << "\t" << "Grade:" << grade << endl;
}
CStudent CStudent::Input()
{
	string name;
	string id;
	string major;
	string grade;
	cout << "Input name:>";
	getline(cin, name);
	cout << "Input id:>";
	getline(cin, id);
	cout << "Input major:>";
	getline(cin, major);
	cout << "Input grade:>";
	getline(cin, grade);
	CStudent a(name, id, major, grade);
	cout << endl;
	return a;
}
int main()
{
	CStudent s("Lee min su", "10010", "Elect", "2");
	s.ShowData();
	CStudent a[4];
	for (int i = 0; i < 4; i++)
	{
		cout << "Enter the " << i + 1 << " student:" << endl;
		a[i] = a[i].Input();
	}
	for (int i = 0; i < 4; i++)
	{
		a[i].ShowData();
	}
	return 0;
}