#include"class.h"
#include<cstdio>
#include<Windows.h>
#include<conio.h>
#define MAX 80
void fClean(char* pc_screen)
{
	memset(pc_screen, ' ', MAX);
	pc_screen[MAX] = '\0';
}
void fDraw(Character& r_player, Character& r_enemy, char* pc_screen)
{
	r_player.setInScreen(pc_screen);
	r_enemy.setInScreen(pc_screen);
	for (int i = 0; i < MAX; i++)
	{
		r_player.setBullet(i,r_enemy,pc_screen);
		r_enemy.setBullet(i, r_player,pc_screen);
	}
}
void keyDown(Character& r_player, Character& r_enemy, char* pc_screen)
{
	if (_kbhit() == 0)return;
	int i_ch = _getch();
	if (224 == i_ch)
	{
		i_ch = _getch();
		switch (i_ch)
		{
		case 75:r_player.movePos(-1); break;
		case 77:r_player.movePos(1); break;
		case 72:r_enemy.movePos(-1); break;
		case 80:r_enemy.movePos(1); break;
		default:
			break;
		}
	}
	else if (' ' == i_ch)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (r_player.getBullet(i).getPos() == -1)
			{
				r_player.getBullet(i).setPos(r_player.getPos());
				break;
			}
		}
	}
	else if ('a' == i_ch)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (r_enemy.getBullet(i).getPos() == -1)
			{
				r_enemy.getBullet(i).setPos(r_enemy.getPos());
				break;
			}
		}
	}
}
void fUpdate(char* pc_screen, Character& r_player, Character& r_enemy)
{
	system("cls");
	printf("%d%77d\n", r_player.getHp(), r_enemy.getHp());
	printf("%s\r", pc_screen);
	Sleep(50);
}
int main()
{
	char ca_screen[MAX];
	Character player(0, "^_^", 10), enemy(77, "*_*", 10);
	while (1)
	{
		fClean(ca_screen);
		fDraw(player, enemy, ca_screen);
		keyDown(player, enemy, ca_screen);
		fUpdate(ca_screen, player, enemy);
	}
	return 0;
}