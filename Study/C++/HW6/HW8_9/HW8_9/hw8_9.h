#pragma once
#include<string>
#include<iostream>
using namespace std;
class Seat
{
	bool mb_seat_select;
	string ms_name;
public:
	Seat():mb_seat_select(0),ms_name("__"){}
	void setName(string s_name) { ms_name = s_name; }
	string getName() { return ms_name; }
	void setSeat(bool b_set) { mb_seat_select = b_set; }
	bool getIsSeatSelect() { return mb_seat_select; }
};
class Line
{
	int mi_time;
	int mi_seatmax;
	Seat* mp_seat;
public:
	Line(int i_time = 0) :mi_time(i_time), mi_seatmax(8) {mp_seat = new Seat[8];}
	void setTime(int i_time=0) { mi_time = i_time; }
	int getTime() { return mi_time; }
	int getSeatMax() { return mi_seatmax; }
	Seat* getSeat(int i_index) { return &mp_seat[i_index]; }
	~Line()
	{
		delete[]mp_seat;
	}
};
class AirLine
{
	 Line* mp_line;
public:
	AirLine()
	{ 
		mp_line = new Line[3];
		mp_line[0].setTime(7); 
		mp_line[1].setTime(12);
		mp_line[2].setTime(17);
	}
	Line* getLine(int i_index) { return &mp_line[i_index]; }
	~AirLine()
	{
		delete[]mp_line;
	}

};
class Console
{
	 AirLine* m_airline;
public:
	Console(AirLine* airline):m_airline(airline){}
	void fSelect()const
	{
		if (m_airline == 0)return;
		bool flag = 1;
		while (flag)
		{		
			int i_select = 0;
			int i_time = 0;
			string s_name = "__";
			int i_num = 0;
			cout << "Select:1, Refund:2, Look:3, Exit:4>>";
			cin >> i_select;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore();
				cin >> i_select;
			}
			if (i_select == 1)
			{
				cout << "7:00->1, 12:00->2, 17:00->3>>";
				cin >> i_time;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore();;
					cin >> i_time;
				}
				for (int i = 0; i < 8; i++)
				{
					cout << m_airline->getLine(i_time-1)->getSeat(i)->getName() << " ";
				}
				cout << endl << "Input your seat number>>" ;
				cin >> i_num;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore();
					cin >> i_num;
				}
				cout << "Input your name>>";
				cin >> s_name;
				if (m_airline->getLine(i_time - 1)->getSeat(i_num - 1)->getIsSeatSelect() == 0)
				{
					m_airline->getLine(i_time-1)->getSeat(i_num-1)->setName(s_name);
					m_airline->getLine(i_time - 1)->getSeat(i_num - 1)->setSeat(1);
				}
				else
				{
					cout << "The seat has been taken" << endl;
				}
			}
			if (i_select == 2)
			{
				cout << "7:00->1, 12:00->2, 17:00->3>>";
				cin >> i_time;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore();
					cin >> i_time;
				}
				for (int i = 0; i < 8; i++)
				{
					cout << m_airline->getLine(i_time - 1)->getSeat(i)->getName() << " ";
				}
				cout <<endl<< "Input your seat number>>";
				cin >> i_num;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore();
					cin >> i_num;
				}
				cout << "Input your name>>";
				cin >> s_name;
				if ((m_airline->getLine(i_time - 1)->getSeat(i_num - 1)->getIsSeatSelect() != 0)
					&&(m_airline->getLine(i_time - 1)->getSeat(i_num - 1)->getName()==s_name))
				{
					m_airline->getLine(i_time - 1)->getSeat(i_num - 1)->setSeat(0);
					m_airline->getLine(i_time - 1)->getSeat(i_num - 1)->setName("__");
				}
				else
				{
					cout << "Error Information!" << endl;
				}
			}
			if (i_select == 3)
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						cout << m_airline->getLine(i)->getSeat(j)->getName()<<" ";
					}
					cout << endl;
				}
			}
			if (i_select == 4)
			{
				flag = 0;
				break;
			}
		}
	}

};