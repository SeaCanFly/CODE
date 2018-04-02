#pragma once
#include<iostream>
#include<string>
using namespace std;
class Converter
{
protected:
	double ratio;
	virtual double convert(double src) = 0;
	virtual string getSourceString() = 0;
	virtual string getDestString() = 0;
public:
	Converter(double ratio) { this->ratio = ratio; }
	void run()
	{
		double src;
		cout << getSourceString() << "->" << getDestString()<<endl;
		cout << getSourceString() << " input>>";
		cin >> src;
		cout << "result:" << convert(src) << getDestString() << endl;
	}
};
class WonToDollar:public Converter
{
	//double src;
	//double dest;
	string dest;
	string src;
public:
	WonToDollar(double d_ratio) :Converter(d_ratio),src("Korean won"),dest("Dollar") {}
	string getSourceString() { return src; }
	string getDestString() { return dest; }
	double convert(double src)
	{
		return src / ratio;
	}
};