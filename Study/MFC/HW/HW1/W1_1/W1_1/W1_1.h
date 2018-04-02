/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #1_1
Visual Studio 2015
*/

#include<iostream>
#include<string>
using namespace std;
class CStudent
{
public:
	string name;
	string id;
	string major;
	string grade;
	void ShowData();
	CStudent Input();
	CStudent();
	CStudent(string , string , string , string );	
	~CStudent(){}
};