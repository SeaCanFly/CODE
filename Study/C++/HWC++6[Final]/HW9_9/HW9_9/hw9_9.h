#pragma once
#include<string>
#include<iostream>
using namespace std;
class Print
{
protected:
	string ms_model;
	string ms_manufacturer;
	int mi_printed_count;
	int mi_avaliable_count;
	virtual void print(int pages) = 0;
	virtual void show() = 0;
public:
	Print(string s_model = "", string s_mf = "", int i_acount = 0)
		:ms_model(s_model), ms_manufacturer(s_mf), mi_avaliable_count(i_acount), mi_printed_count(0) {}
};
class InkJetPrinter :public Print
{
	int mi_available_ink;
public:
	InkJetPrinter(string s_model = "Ink", string s_mf = "Officejet,HP",int i_acount=5,int i_aink=10)
		:Print(s_model,s_mf,i_acount),mi_available_ink(i_aink){}
	void show()
	{
		cout << ms_model << ":" << ms_manufacturer << ", avaliable page:" << mi_avaliable_count << ", avaliable ink:" << mi_available_ink << endl;
	}
	void print(int pages)
	{
		
		if (mi_avaliable_count >= pages&&mi_available_ink >= pages)
		{
			mi_printed_count += pages;
			mi_avaliable_count -= pages;
			mi_available_ink -= pages;
		}
		else
		{
			cout << "Short of ink or paper" << endl;
		}
	}
};
class LaserPrinter :public Print
{
	int mi_available_toner;
	int mi_count;
public:
	LaserPrinter(string s_model = "Laser", string s_mf = "SCX-6x45,samsung", int i_acount = 3, int i_atoner = 20)
		:Print(s_model, s_mf, i_acount), mi_available_toner(i_atoner),mi_count(0) {}
	void show()
	{
		cout << ms_model << ":" << ms_manufacturer << ", avaliable page:" << mi_avaliable_count << ", avaliable ink:" << mi_available_toner << endl;
	}
	void print(int pages)
	{

		if (mi_avaliable_count >= pages&&mi_available_toner >= (mi_count + pages * 2))
		{
			mi_printed_count += pages;
			mi_avaliable_count -= pages;
			if ((pages + mi_count) % 2 == 0)
			{
				pages = (pages + mi_count) / 2;
				mi_count = 0;
			}
			else
			{
				pages = pages / 2;
				mi_count++;
			}
			mi_available_toner -= pages;
		}
		else
		{
			cout << "Short of ink or paper" << endl;
		}
	}
};