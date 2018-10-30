
#include<iostream>
#include<cstdio>
#include<string.h>
#include<Windows.h>
#include<conio.h>
using namespace std;
#define SCREEN_SIZE 79
void draw(char* screen, int bullet_pos, int direction,int player_pos,const char *face)
{
	//screen[bullet_pos] = (direction == 0) ? '>' : '<';
	strncpy(screen + bullet_pos, (direction==0)?"-->":"<--",(direction==0)?strlen("-->"):strlen("<--"));
	strncpy(screen+player_pos,face,strlen(face));
}
void update(int* bullet_pos, int* direction)
{
	if (*direction == 0)
	{
		//(*bullet_pos)++;
		if (*bullet_pos >= SCREEN_SIZE)
		{
			*direction = 1;
			*bullet_pos = SCREEN_SIZE - 1;
		}
	}
	else
	{
		//(*bullet_pos)--;
		if (*bullet_pos<0)
		{
			*bullet_pos = 0;
			*direction = 0;
		}
	}
}
void render(char* screen)
{
	screen[SCREEN_SIZE]='\0';
	printf("%s",screen);
}
void process_input(int& player_pos,int& bullet_pos)
{
	if(_kbhit()==0)return;
	int ch=_getch();
	if (ch == 224)
	{
		ch=_getch();
		if(ch=75)player_pos--;
		if(ch=77)player_pos++;
	}
	else
	{
		if(ch=='a')player_pos--;
		if(ch=='s')player_pos++;
		if(ch=='w')bullet_pos++;
		if(ch=='x')bullet_pos--;
	}

}
int main()
{
	int direction = 0;
	char screen[SCREEN_SIZE + 1];
	int bullet_pos = 0;
	char face[]="^_^";
	int player_pos=10;
	while (1)
	{
		memset(screen, ' ', SCREEN_SIZE);
		process_input(player_pos,bullet_pos);
		draw(screen, bullet_pos, direction,player_pos,face);
		update(&bullet_pos, &direction);

		screen[SCREEN_SIZE] = '\0';
		printf("%s\r", screen);
		Sleep(33);
	}
	return 0;
}