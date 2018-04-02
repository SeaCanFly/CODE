#include<iostream>  
#include<windows.h>  
#include<conio.h>  
#include<time.h>
using namespace std;

struct node {
	int x, y;
};

node s[110], food, tail;//s是蛇的身体的坐标 food是食物坐标  tail是尾部坐标，你要在移动后将它覆盖   
bool eat = true;//记录食物是否吃过   
int len = 3, face = 4;//len是蛇的长度  face是朝向   
int score = 0;//游戏得分   
int speed = 0, Min = 0;//speed是蛇的移动速度(游戏的刷新速度)  Min是移动速度上限   

void gotoxy(int y, int x) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void color(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
	/*
	字
	1   深蓝色
	2   深绿色
	3   深青色
	4   深红色
	5   深粉色
	6   深黄色
	7   深白色
	8   灰色
	9   浅蓝色
	10  浅绿色
	11  浅青色
	12  浅红色
	13  浅粉色
	14  浅黄色
	15  浅白色


	背景
	1~15        黑色
	16~31       深蓝色
	32~47       深绿色
	48~63       深青色
	64~79       深红色
	80~95       深粉色
	96~111      深黄色
	112~127     深白色
	128~143     灰色
	144~159     浅蓝色
	160~175     浅绿色
	176~191     浅青色
	192~207     浅红色
	208~223     浅粉色
	224~239     浅黄色
	240~255     浅白色
	*/
}

int main() {
	while (1) {
		system("cls");
		cout << "请选择难度：" << endl;
		cout << "1.低" << endl;
		cout << "2.中" << endl;
		cout << "3.高" << endl;
		char ch;
		ch = _getch();
		if (ch == '1') {
			speed = 225;
			Min = 175;
			break;
		}
		if (ch == '2') {
			speed = 175;
			Min = 125;
			break;
		}
		if (ch == '3') {
			speed = 125;
			Min = 65;
			break;
		}
	}
	system("cls");
	s[1].x = 10;
	s[1].y = 11;
	s[2].x = 10;
	s[2].y = 10;
	s[3].x = 10;
	s[3].y = 9;
	tail.x = 10;
	tail.y = 8;
	for (int i = 0; i <= 21; i++) {
		color(11);
		cout << "□";
	}cout << endl;
	for (int i = 1; i <= 20; i++) {
		color(11);
		cout << "□";
		for (int j = 1; j <= 20; j++) {
			color(10);
			cout << "■";
		}
		color(11);
		cout << "□" << endl;
	}
	for (int i = 0; i <= 21; i++) {
		color(11);
		cout << "□";
	}cout << endl;
	_getch();
	while (1) {
		Sleep(speed);
		if (eat == true) {
			srand(unsigned(time(NULL)));
			food.x = rand() % 20 + 1;
			food.y = rand() % 20 + 1;
			eat = false;
			for (int i = 1; i <= len; i++) {
				if (s[i].x == food.x && s[i].y == food.y) {
					cout << food.x << ' ' << food.y << endl;
					cout << s[i].x << ' ' << s[i].y << endl;
					eat = true;
					break;
				}
			}
			if (eat == true) {
				continue;
			}
		}

		gotoxy(food.x, food.y * 2);
		color(12);
		cout << "●";
		color(14);
		gotoxy(9, 24 * 2);
		cout << "目前得分：" << score << endl;
		color(14);
		gotoxy(10, 24 * 2);
		cout << "当前速度：" << speed << "(越小越快)" << endl;
		for (int i = 1; i <= len; i++) {
			if (i != 1 && s[1].x == s[i].x && s[1].y == s[i].y) {
				system("cls");
				putchar(7);
				system("cls");
				cout << "您最后的得分为：" << score << endl;
				system("pause");
				return 0;
			}
			gotoxy(s[i].x, s[i].y * 2);
			color(14);
			cout << "★";
		}

		gotoxy(tail.x, tail.y * 2);
		color(10);
		cout << "■";

		gotoxy(0, 0);
		color(11);
		cout << "□";

		if (_kbhit()) {
			char c;
			c = _getch();
			if (c == 'w' && face != 2) {
				face = 1;
			}
			if (c == 's' && face != 1) {
				face = 2;
			}
			if (c == 'a' && face != 4) {
				face = 3;
			}
			if (c == 'd' && face != 3) {
				face = 4;
			}
		}



		node x;
		if (face == 1) {
			x.x = s[1].x - 1;
			x.y = s[1].y;
		}
		if (face == 2) {
			x.x = s[1].x + 1;
			x.y = s[1].y;
		}
		if (face == 3) {
			x.x = s[1].x;
			x.y = s[1].y - 1;
		}
		if (face == 4) {
			x.x = s[1].x;
			x.y = s[1].y + 1;
		}

		if (s[1].x == food.x && s[1].y == food.y) {
			score++;
			eat = true;
			len++;
			speed -= 5;
			if (speed<Min)speed = Min;
			continue;
		}

		if (s[1].x>20) {
			system("cls");
			putchar(7);
			break;
		}
		if (s[1].x<1) {
			system("cls");
			putchar(7);
			break;
		}
		if (s[1].y>20) {
			system("cls");
			putchar(7);
			break;
		}
		if (s[1].y<1) {
			system("cls");
			putchar(7);
			break;
		}

		for (int i = 1; i <= len; i++) {
			swap(x.x, s[i].x);
			swap(x.y, s[i].y);
		}
		tail.x = x.x;
		tail.y = x.y;

	}
	system("cls");
	cout << "您最后的得分为：" << score << endl;
	system("pause");

	return 0;
}