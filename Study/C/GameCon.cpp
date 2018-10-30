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
	void draw(char* canvas)const
	{
		if (pos >= 0 && pos < SCREEN_SIZE)
		{
			strncpy(canvas + pos, shape, strlen(shape));
		}
	}
};
struct Bullet:public GameObject
{
	/*struct GameObject mydata;*/
	bool is_fired;
	void draw(char* canvas, const GameObject* player, const GameObject* enermy)
	{
		if (/*mydata.*/pos == -1)return;
		if (player->pos </* mydata.*/pos)
		{
			strncpy(canvas +/* mydata.*/pos, ">", strlen(">"));

		}
		else if (player->pos > enermy->pos)
		{
			strncpy(canvas +/* mydata.*/pos, "<", strlen("<"));
		}
	}
};
void clear_screen(char* screen)
{
	memset(screen, ' ', SCREEN_SIZE);
}
void process_input(GameObject* player, GameObject* enermy, GameObject bullets[],int bullets_len)
{
	if (_kbhit() == 0)return;
	int ch = _getch();
	if (ch == 224)
	{
		ch = _getch();
		if (ch == 75) (player->pos)--;
		if (ch == 77) (player->pos)++;
		if (ch == 80) (enermy->pos)++;
		if (ch == 72) (enermy->pos)--;
	}
	else if (ch == ' ')
	{
		for (int i = 0; i < bullets_len; i++)
		{
			if (bullets[i].pos >= 0)continue;
			if (bullets[i].pos == -1)
			{
				bullets[i].pos = player->pos;
				break;
			}
		}
	}

}
void draw(char* screen, const GameObject* player, const GameObject* enermy, const GameObject bullets[], int bullets_len)
{
	if (screen == NULL)return;
	/*((GameObject*)player)->draw(screen);
	const_cast<GameObject*>(enermy)->draw(screen);*/
	player->draw(screen);
	enermy->draw(screen);
	for (int i = 0; i < bullets_len; i++)
	{
		if (bullets[i].pos == -1)continue;
		if (player->pos < enermy->pos)
		{
			strncpy(screen + bullets[i].pos, ">", strlen(">"));

		}
		else if (player->pos > enermy->pos)
		{
			strncpy(screen + bullets[i].pos, "<", strlen("<"));
		}
	}
}

void update(GameObject* player, GameObject* enermy, GameObject bullets[], int bullets_len)
{
	for (int i = 0; i < bullets_len; i++)
	{
		if (bullets[i].pos == -1)continue;
		if (bullets[i].pos == enermy->pos || bullets[i].pos < 0 || bullets[i].pos >= SCREEN_SIZE)
			{
				bullets[i].pos = -1;
				continue;
			}
		if (player->pos < enermy->pos)
		(bullets[i].pos)++;
		if (player->pos > enermy->pos)
		(bullets[i].pos)--;
	}

	
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
	const int bullets_len = 80;
	char screen[SCREEN_SIZE + 1];
	GameObject player;
	GameObject enermy;
	GameObject bullet[bullets_len];
	
	strcpy(player.shape, "^_^");
	player.pos = rand() % SCREEN_SIZE;

	strcpy(enermy.shape, "@_@");
	enermy.pos = rand() % SCREEN_SIZE;

	for (int i = 0; i < bullets_len; i++)
	{
		strcpy(bullet[i].shape, ">");
		bullet[i].pos = -1;
	}
	

	while (1)
	{
		clear_screen(screen);
		process_input(&player, &enermy, bullet,bullets_len);
		draw(screen, &player, &enermy, bullet,bullets_len);
		update(&player, &enermy, bullet,bullets_len);
		render(screen);
	}
	return 0;
}