#include"Node.h"
#include"NodeManager.h"
#include<iostream>
#include<cstdio>
#include<conio.h>
#include<Windows.h>
#include<ctime>
using namespace std;
#define MAX 25
void fClean()
{
	COORD t = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), t);
	
	Sleep(90);
}
NodeManager createFood(NodeManager& head)
{
	int i_x = rand() % MAX;
	int i_y = rand() % MAX;
	NodeManager food(i_x, i_y);
	food.getNode()->setShape('#');
	return food;
}

void fReset(NodeManager& head)
{

	NodeManager* p = (head.getNode()->getPNext());
	while (p->getNode()->getPNext()!= 0)
	{
		NodeManager* temp = p;
		head.getNode()->setPNext(p->getNode()->getPNext());
		delete temp;
		p = p->getNode()->getPNext();
	}	
	head.getNode()->setPosition(0, 3);
	head.getNode()->getPNext()->getNode()->setPosition(0, 2);
}
void fDraw(NodeManager& head,NodeManager& food)
{
	
	bool flag = 0;
	for (int i = 0; i <= MAX; i++)
	{
		for (int j = 0; j <= MAX; j++)
		{
			NodeManager* p = &head;
	
			while (p != 0)
			{
				if (p->getNode()->getCheck(i, j)==1)
				{
					cout << p->getNode()->getShape();
					flag = 1;
					break;
				}
				
				p = p->getNode()->getPNext();
			}

			 if (food.getNode()->getCheck(i, j)==1&&food.getNode()->getExist()==0)
				{
					cout << food.getNode()->getShape();
					flag = 1;
				}
			if (flag == 0)
			{
				cout << ' ';
			}
			flag = 0;
		}
		cout << '|' << "\n";
		if (i == MAX)
		{
			for (int k = 0; k <= MAX; k++)
			{
				cout << "-";
			}
			cout << '|' << "\n";
		}
	}
	cout << endl;
}
void keyDown(Node& head)
{
	if (_kbhit() == 0)return;
	int i_ch = _getch();
	if (i_ch = 224)
	{
		i_ch = _getch();
		if (i_ch == 75)
		{
			int i_temp = head.getDirect();
			if (i_temp != 2 /*&& head.getX() > 0*/)
			{
				head.setDirect(1);
				head.setSpeed(1);
			}
		}
		if (i_ch == 77)
		{
			int i_temp = head.getDirect();
			if (i_temp != 1 /*&& head.getX() < MAX*/)
			{
				head.setDirect(2);
				head.setSpeed(1);
			}
		}
		if (i_ch == 72)
		{
			if (head.getDirect() != 4 /*&& head.getY() > 0*/)
			{
				head.setDirect(3);
				head.setSpeed(1);
			}
		}
		if (i_ch == 80)
		{
			if (head.getDirect() != 3 /*&& head.getY() < MAX*/)
			{
				head.setDirect(4);
				head.setSpeed(1);
			}
		}
	}
}
void fMoving(NodeManager& head,NodeManager& food,bool& b_create_food)
{
	int i_direct = head.getNode()->getDirect();
	NodeManager* p = &head;

	if (i_direct == 1)
	{
		if (head.getNode()->getX() == food.getNode()->getX() && head.getNode()->getY()-1 == food.getNode()->getY())
		{
			head.getNode()->addNode(food);
			b_create_food = 1;
			return ;
		}
		int i_hx = head.getNode()->getX();
		int i_hy = head.getNode()->getY();
		int i_nx = 0, i_ny = 0,i_px=0,i_py=0;

		bool f = 0;
		while (p != 0)
		{
			if (f == 0)
			{
				i_px = p->getNode()->getX();
				i_py = p->getNode()->getY();
				f = 1;
			}
			else
			{
				 i_px = i_nx;
				 i_py = i_ny;
			}
			if (p->getNode()->getPNext() != 0)
			{
				i_nx = p->getNode()->getPNext()->getNode()->getX();
				i_ny = p->getNode()->getPNext()->getNode()->getY();
				p->getNode()->getPNext()->getNode()->setPosition(i_px, i_py);
			}
			p = p->getNode()->getPNext();
		}
		head.getNode()->movePosition(0, -1);
	}
	if (i_direct == 2)
	{
		if (head.getNode()->getX() == food.getNode()->getX() && head.getNode()->getY() + 1 == food.getNode()->getY())
		{
			head.getNode()->addNode(food);
			b_create_food = 1;
			return ;
		}
		int i_hx = head.getNode()->getX();
		int i_hy = head.getNode()->getY();
		int i_nx = 0, i_ny = 0, i_px = 0, i_py = 0;

		bool f = 0;
		while (p != 0)
		{
			if (f == 0)
			{
				i_px = p->getNode()->getX();
				i_py = p->getNode()->getY();
				f = 1;
			}
			else
			{
				i_px = i_nx;
				i_py = i_ny;
			}
			if (p->getNode()->getPNext() != 0)
			{
				i_nx = p->getNode()->getPNext()->getNode()->getX();
				i_ny = p->getNode()->getPNext()->getNode()->getY();
				p->getNode()->getPNext()->getNode()->setPosition(i_px, i_py);
			}
			p = p->getNode()->getPNext();
		}
		
		head.getNode()->movePosition(0, 1);
	}
	if (i_direct == 3)
	{	
		if (head.getNode()->getX()-1 == food.getNode()->getX() && head.getNode()->getY() == food.getNode()->getY())
		{
			head.getNode()->addNode(food);
			b_create_food = 1;
			return ;
		}
		int i_hx = head.getNode()->getX();
		int i_hy = head.getNode()->getY();
		int i_nx = 0, i_ny = 0, i_px = 0, i_py = 0;

		bool f = 0;
		while (p != 0)
		{
			if (f == 0)
			{
				i_px = p->getNode()->getX();
				i_py = p->getNode()->getY();
				f = 1;
			}
			else
			{
				i_px = i_nx;
				i_py = i_ny;
			}
			if (p->getNode()->getPNext() != 0)
			{
				i_nx = p->getNode()->getPNext()->getNode()->getX();
				i_ny = p->getNode()->getPNext()->getNode()->getY();
				p->getNode()->getPNext()->getNode()->setPosition(i_px, i_py);
			}
			p = p->getNode()->getPNext();
		}
		head.getNode()->movePosition(-1, 0);
	}
	if (i_direct == 4)
	{
		if (head.getNode()->getX()+1 == food.getNode()->getX() && head.getNode()->getY() == food.getNode()->getY())
		{
			head.getNode()->addNode(food);
			b_create_food = 1;
			return ;
		}
		int i_hx = head.getNode()->getX();
		int i_hy = head.getNode()->getY();
		int i_nx = 0, i_ny = 0, i_px = 0, i_py = 0;

		bool f = 0;
		while (p != 0)
		{
			if (f == 0)
			{
				i_px = p->getNode()->getX();
				i_py = p->getNode()->getY();
				f = 1;
			}
			else
			{
				i_px = i_nx;
				i_py = i_ny;
			}
			if (p->getNode()->getPNext() != 0)
			{
				i_nx = p->getNode()->getPNext()->getNode()->getX();
				i_ny = p->getNode()->getPNext()->getNode()->getY();
				p->getNode()->getPNext()->getNode()->setPosition(i_px, i_py);
			}
			p = p->getNode()->getPNext();
		}
		
		head.getNode()->movePosition(1, 0);
	}
}
void fCheck(NodeManager& head)
{
	int i_hx = head.getNode()->getX();
	int i_hy = head.getNode()->getY();
	if (i_hx<0 || i_hy<0 || i_hx>MAX || i_hy>MAX)
	{
		head.getNode()->setDirect(0);
		head.getNode()->setSpeed(0);
		fReset(head);
	}

}
int main()
{
	NodeManager head(0, 3);
	NodeManager end(0, 2);
	head.getNode()->setPNext(&end);
	srand((unsigned)time(0));

	bool b_create_food = 1;//NodeManager food;
	int i_x = rand() % MAX;
	int i_y = rand() % MAX;
	NodeManager food(i_x, i_y);
	food.getNode()->setShape('#');
	while (1)
	{
		
		/*if (b_create_food == 1)
		{
			food=createFood(head);
			b_create_food = 0;
		}*/
		fClean();
		fDraw(head,food);

		keyDown(*head.getNode());
		fMoving(head,food,b_create_food);
		fCheck(head);
	}
	return 0;
}