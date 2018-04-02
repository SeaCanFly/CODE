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
void fDraw(Object& player, Object& enemy, Object& bullet, string& rbattle_line)
{
	int	ippos = player.getPos();
	int iepos = enemy.getPos();
	int ibpos = bullet.getPos();
	player.setPosition(ippos, rbattle_line);
	enemy.setPosition(iepos, rbattle_line);
	if (ibpos == -1)return;
	if (ibpos < 0 || ibpos > MAX || ibpos == iepos)
	{
		rbattle_line.replace(ibpos, bullet.getShape().size(), " ");
		bullet.setPos(-1);
	}
	else
	{
		if (ippos < iepos)
		{
			bullet.setShape(">");
			bullet.setPosition(ibpos, rbattle_line);
			bullet.movePos(1);
		}
		if (ippos >= iepos)
		{
			bullet.setShape("<");
			bullet.setPosition(ibpos, rbattle_line);
			bullet.movePos(-1);
		}
	}
}
void fKeyDown(Object& player, Object& enemy, Object& bullet)
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
		if (bullet.getPos() == -1)
			bullet.setPos(player.getPos());
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
	Object player(0, "^_^"), enemy(60, "@_@"), bullet(-1, "");

	while (1)
	{
		fInitialize(sbattle_line);
		fDraw(player, enemy, bullet, sbattle_line);
		fKeyDown(player, enemy, bullet);
		fUpdate(sbattle_line);
	}
	return 0;
}