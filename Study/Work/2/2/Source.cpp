#include<iostream>  
#include<windows.h>  
#include<conio.h>  
#include<time.h>
using namespace std;

struct node {
	int x, y;
};

node s[110], food, tail;//s���ߵ���������� food��ʳ������  tail��β�����꣬��Ҫ���ƶ���������   
bool eat = true;//��¼ʳ���Ƿ�Թ�   
int len = 3, face = 4;//len���ߵĳ���  face�ǳ���   
int score = 0;//��Ϸ�÷�   
int speed = 0, Min = 0;//speed���ߵ��ƶ��ٶ�(��Ϸ��ˢ���ٶ�)  Min���ƶ��ٶ�����   

void gotoxy(int y, int x) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void color(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
	/*
	��
	1   ����ɫ
	2   ����ɫ
	3   ����ɫ
	4   ���ɫ
	5   ���ɫ
	6   ���ɫ
	7   ���ɫ
	8   ��ɫ
	9   ǳ��ɫ
	10  ǳ��ɫ
	11  ǳ��ɫ
	12  ǳ��ɫ
	13  ǳ��ɫ
	14  ǳ��ɫ
	15  ǳ��ɫ


	����
	1~15        ��ɫ
	16~31       ����ɫ
	32~47       ����ɫ
	48~63       ����ɫ
	64~79       ���ɫ
	80~95       ���ɫ
	96~111      ���ɫ
	112~127     ���ɫ
	128~143     ��ɫ
	144~159     ǳ��ɫ
	160~175     ǳ��ɫ
	176~191     ǳ��ɫ
	192~207     ǳ��ɫ
	208~223     ǳ��ɫ
	224~239     ǳ��ɫ
	240~255     ǳ��ɫ
	*/
}

int main() {
	while (1) {
		system("cls");
		cout << "��ѡ���Ѷȣ�" << endl;
		cout << "1.��" << endl;
		cout << "2.��" << endl;
		cout << "3.��" << endl;
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
		cout << "��";
	}cout << endl;
	for (int i = 1; i <= 20; i++) {
		color(11);
		cout << "��";
		for (int j = 1; j <= 20; j++) {
			color(10);
			cout << "��";
		}
		color(11);
		cout << "��" << endl;
	}
	for (int i = 0; i <= 21; i++) {
		color(11);
		cout << "��";
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
		cout << "��";
		color(14);
		gotoxy(9, 24 * 2);
		cout << "Ŀǰ�÷֣�" << score << endl;
		color(14);
		gotoxy(10, 24 * 2);
		cout << "��ǰ�ٶȣ�" << speed << "(ԽСԽ��)" << endl;
		for (int i = 1; i <= len; i++) {
			if (i != 1 && s[1].x == s[i].x && s[1].y == s[i].y) {
				system("cls");
				putchar(7);
				system("cls");
				cout << "�����ĵ÷�Ϊ��" << score << endl;
				system("pause");
				return 0;
			}
			gotoxy(s[i].x, s[i].y * 2);
			color(14);
			cout << "��";
		}

		gotoxy(tail.x, tail.y * 2);
		color(10);
		cout << "��";

		gotoxy(0, 0);
		color(11);
		cout << "��";

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
	cout << "�����ĵ÷�Ϊ��" << score << endl;
	system("pause");

	return 0;
}