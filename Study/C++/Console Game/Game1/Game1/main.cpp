#include"class.h"
#include<cstdio>
#include<cstdlib>
#include<conio.h>
#include<Windows.h>
#define MAX 80
void fClean(char* pc_screen)
{
	memset(pc_screen, ' ', MAX);
}
void fDraw(char* pc_screen, Object& r_player, Object& r_enemy, Object a_bullet[], int n)
{
	r_player.setInScreen(pc_screen);
	r_enemy.setInScreen(pc_screen);
	for (int i = 0; i < n; i++)
	{
		int i_bpos = a_bullet[i].getPos();
		if (i_bpos == -1)continue;
		if (i_bpos == r_enemy.getPos())
		{
			if (r_enemy.getHp() > 0)
			{
				r_enemy.setHp(r_enemy.getHp() - 1);
			}
			else
			{
				r_enemy.setHp(10);
			}
			a_bullet[i].setPos(-1);
			a_bullet[i].setShape("");
		}
		else
		{
			if (r_player.getPos()>r_enemy.getPos())
			{
				a_bullet[i].setShape("<");
				a_bullet[i].setInScreen(pc_screen);
				a_bullet[i].setPos(i_bpos - 1);
			}
			else
			{
				a_bullet[i].setShape(">");
				a_bullet[i].setInScreen(pc_screen);
				a_bullet[i].setPos(i_bpos + 1);
			}
		}
	}
}
void keyDown(Object& r_player, Object& r_enemy, Object a_bullet[], int n)
{
	int i_ppos = r_player.getPos();
	int i_epos = r_enemy.getPos();
	if (_kbhit() == 0)return;
	int i_check = _getch();
	if (i_check == 224)
	{
		i_check = _getch();
		switch (i_check)
		{
		case 72:if (i_epos>0)
			r_enemy.setPos(i_epos - 2);
			break;
		case 77:if (i_ppos + strlen(r_player.getShape())<MAX - 1)
			r_player.setPos(i_ppos + 1);
			break;
		case 75:if (i_ppos>0)
			r_player.setPos(i_ppos - 1);
			break;
		case 80:if (i_epos + strlen(r_enemy.getShape())<MAX - 1)
			r_enemy.setPos(i_epos + 2);
			break;
		default:
			break;
		}
	}
	else if (i_check == ' ')
	{
		for (int i = 0; i < n; i++)
		{
			if (a_bullet[i].getPos() == -1)
			{
				a_bullet[i].setPos(i_ppos);
				break;
			}
		}
	}
}
void fUpdate(char* pc_screen, const Object& r_player, const Object& r_enemy)
{
	pc_screen[MAX - 1] = '\0';
	system("cls");
	printf("%d%60d\n", r_player.getHp(), r_enemy.getHp());
	printf("%s\r", pc_screen);
	Sleep(50);
}
int main()
{
	char ca_screen[MAX] = { '\0' };
	Object player(0, "^_^", 10), enemy(60, "@_@", 10), a_bullet[MAX];

	while (1)
	{
		fClean(ca_screen);
		fDraw(ca_screen, player, enemy, a_bullet, MAX);
		keyDown(player, enemy, a_bullet, MAX);
		fUpdate(ca_screen, player, enemy);
	}
	return 0;
}