/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #9_9
Visual Studio 2015
*/
#include"hw9_9.h"
int main()
{
	InkJetPrinter* inkpt = new InkJetPrinter();
	LaserPrinter* laserpt = new LaserPrinter();
	bool flag = 1;
	while (flag)
	{
		int i_pages = 0;
		int i_select = 0;
		char c_contine = '\0';
		cout << "have 2 printer ready:" << endl;
		inkpt->show();
		laserpt->show();
		cout << "printer(1:ink,2:laser) and input the copies>>";
		cin >> i_select >> i_pages;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cin >> i_select >> i_pages;
		}
		if (i_select == 1)
		{
			inkpt->print(i_pages);
		}
		if (i_select == 2)
		{
			laserpt->print(i_pages);
		}
		inkpt->show();
		laserpt->show();
		cout << "Continue printing?[y/n]>>";
		while (cin >> c_contine)
		{
			if (c_contine == 'n')
			{
				flag = 0;
				break;
			}
			if (c_contine == 'y')
			{
				flag = 1;
				break;
			}
			cin.clear();
			cin.ignore();
		}

	}
	return 0;
}