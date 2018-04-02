/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #3_2
Visual Studio 2015
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ROCK 1
#define PAPER 2
#define SCISSORS 3
int pk(int x, int y)
{
		 if (x == ROCK && y == ROCK) { printf("Tie, Mine is Rock too.\n"); return 3;}
	else if (x == ROCK && y == PAPER){ printf("You lose, Mine is Paper.\n"); return 2;}
	else if (x == ROCK && y == SCISSORS) { printf("You win, Mine is Scissors.\n"); return 1;}
	else if (x == PAPER && y == ROCK) { printf("You win, Mine is Rock.\n"); return 1;}
	else if (x == PAPER && y == PAPER) { printf("Tie, Mine is Paper too.\n"); return 3;}
	else if (x == PAPER && y == SCISSORS) { printf("You lose, Mine is Scissors.\n"); return 2;}
	else if (x == SCISSORS && y == ROCK) { printf("You lose, Mine is Rock.\n"); return 2;}
	else if (x == SCISSORS && y == PAPER) { printf("You win, Mine is Paper.\n"); return 1;}
	else if (x == SCISSORS && y == SCISSORS) { printf("Tie, Mine is Scissors too.\n"); return 3;}
}
int com(int y)
{return rand()% 3 + 1;}
int input()
{
	int x, num, c;
	while (1)
	{
		printf("What is your choice? (1: rock 2: paper 3: scissor 0: quit): \n>");
		num = scanf("%d", &x);
		while (num != 1)
		{
			printf(">");
			while ((c = getchar()) != EOF&&c != '\n');
			num = scanf("%d", &x);
		}
		if ((x >= 0) && (x < 4))
			{return x;}
		else
			{printf("Wrong input. Please input between 1 and 3. Input 0 if you want to quit!\n");}
	}
}
int main()
{
	int a[4] = { 0 }; int p1, p2; int i;
	while (p1 = input())
	{
		unsigned t = time(NULL);
		srand(t);
		p2=com(rand());
		i = pk(p1, p2);
		a[i] = a[i] + 1;
		a[0] = a[0] + 1;
	}
	printf("You tried %d times: %d wins, %d ties, and %d loses\n", a[0], a[1], a[3], a[2]);
	return 0;
}