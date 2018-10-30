#include"HW5.h"
#include<iostream>
#include<Windows.h>
#include<cstdio>
#include<conio.h>
using namespace std;
#define MAX 80
void fInitialize(string& rbattle_line)
{
	rbattle_line.clear();
	rbattle_line.resize(MAX, ' ');
}
void fDraw(Object& player, Object& enemy, string& rbattle_line, Object bullet[], int count)
{
	int	ippos = player.getPos();
	int iepos = enemy.getPos();
	player.setPosition(ippos, rbattle_line);
	enemy.setPosition(iepos, rbattle_line);
	for (int i = 0; i < count; i++)
	{
		int ibpos = bullet[i].getPos();
		if (ibpos == -1)continue;
		if (ibpos < 0 || ibpos > MAX || ibpos == iepos)
		{
			rbattle_line.replace(ibpos, bullet[i].getShape().size(), " ");
			bullet[i].setPos(-1);
			continue;
		}
		else
		{
			if (ippos < iepos)
			{
				bullet[i].setShape(">");
				bullet[i].setPosition(ibpos, rbattle_line);
				bullet[i].movePos(1);
			}
			if (ippos >= iepos)
			{
				bullet[i].setShape("<");
				bullet[i].setPosition(ibpos, rbattle_line);
				bullet[i].movePos(-1);
			}
		}
	}

}
void fKeyDown(Object& player, Object& enemy, Object bullet[], int count)
{
	if (_kbhit() == 0)return;
	int ch = _getch();
	if (224 == ch)
	{
		ch = _getch();
		if (72 == ch)
		{
			enemy.movePos(-1);
		}
		if (75 == ch)
		{
			player.movePos(-1);
		}
		if (77 == ch)
		{
			player.movePos(1);
		}
		if (80 == ch)
		{
			enemy.movePos(1);
		}
	}
	else if (' ' == ch)
	{
		for (int i = 0; i < count; i++)
		{
			if (bullet[i].getPos() == -1)
			{
				bullet[i].setPos(player.getPos());
				break;
			}
		}
	}
}
void fUpdate(string& sbattle_line)
{
	cout << sbattle_line << "\r";
	Sleep(80);
}
int main()
{
	string sbattle_line;
	Object player(0, "^_^"), enemy(60, "@_@"), bullet[MAX];

	while (1)
	{
		fInitialize(sbattle_line);
		fDraw(player, enemy, sbattle_line, bullet, MAX);
		fKeyDown(player, enemy, bullet, MAX);
		fUpdate(sbattle_line);
	}
	return 0;
}