
#include<iostream>
#include<cstdio>
#include<cstring>
#include<Windows.h>
#include<conio.h>
#include<time.h>
using namespace std;
#define SCREEN_SIZE 79
struct GameObject
{
	int pos;
	char shape[5];
};
void clear_screen(char* screen)
{
	memset(screen, ' ', SCREEN_SIZE);
}
void process_input(GameObject& player, GameObject& enermy, GameObject& bullet)
{
	if (_kbhit() == 0)return;
	int ch = _getch();
	if (ch == 224)
	{
		ch = _getch();
		if (ch == 75) (player.pos)--;
		if (ch == 77) (player.pos)++;
		if (ch == 80) (enermy.pos)++;
		if (ch == 72) (enermy.pos)--;
	}
	else if (ch == ' ')
	{
		if (bullet.pos == -1)
			bullet.pos = player.pos;
	}

}
void draw(char* screen, const GameObject& player, const GameObject& enermy, const GameObject& bullet)
{
	if (screen == NULL)return;
	if (player.shape != NULL && player.pos >= 0 && player.pos < SCREEN_SIZE)
		strncpy(screen + player.pos, player.shape, strlen(player.shape));
	if (enermy.shape != NULL && enermy.pos >= 0 && enermy.pos < SCREEN_SIZE)
		strncpy(screen + enermy.pos, enermy.shape, strlen(enermy.shape));
	if (bullet.pos != -1)
	{
		if (player.pos < enermy.pos)
		{
			strncpy(screen + bullet.pos, ">", strlen(">"));

		}
		else if (player.pos > enermy.pos)
		{
			strncpy(screen + bullet.pos, "<", strlen("<"));
		}
	}
}

void update(GameObject & player, GameObject& enermy, GameObject& bullet)
{
	if (bullet.pos == -1)return;
	if (bullet.pos == enermy.pos || bullet.pos < 0 || bullet.pos >= SCREEN_SIZE)
	{
		bullet.pos = -1;
		return;
	}
	if (player.pos < enermy.pos)
		(bullet.pos)++;
	if (player.pos > enermy.pos)
		(bullet.pos)--;
}
void render(char* screen)
{
	screen[SCREEN_SIZE] = '\0';
	printf("%s\r", screen);
	Sleep(80);
}

int main()
{
	srand(time(0));
	char screen[SCREEN_SIZE + 1];
	GameObject player;
	GameObject enermy;
	GameObject bullet;
	strcpy(player.shape, "^_^");
	player.pos = rand() % SCREEN_SIZE;
	strcpy(enermy.shape, "@_@");
	enermy.pos = rand() % SCREEN_SIZE;
	strcpy(bullet.shape, ">");
	bullet.pos = -1;

	while (1)
	{
		clear_screen(screen);
		process_input(player, enermy, bullet);
		draw(screen, player, enermy, bullet);
		update(player, enermy, bullet);
		render(screen);
	}
	return 0;
}