#pragma once

#include<iostream>
#include<string>
using namespace std;
class Person
{
private:
	string name;
public:
	Person() {}
	Person(string name) :name(name) {};
	string getName()
	{
		return name;
	}
	void setPersonName(string n)
	{
		name = n;
	}
};
class Family
{
private:
	Person* p;
	int size;
	string name;
public:
	Family(string name, int size):name(name),size(size),p(new Person[size]){}
	~Family()
	{
		delete[]p;
	}
	void setName(int n,string name)
	{
		p[n].setPersonName(name);
	}
	void show()
	{
		cout << name << " has " << size << " family members:" << endl;
		for (int i = 0; i < size; i++)
		{
			cout<<p[i].getName()<<"  ";
		}
		cout << endl;
	}
};