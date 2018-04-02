/*
name:wangyisen
student id:B577046
game software
homework #2_4
visual studio 2015
*/

#include <stdio.h>
#define M1 "위대한 소원"//15
#define M2 "울트라맨 우주 몬스터 대결전"//All
#define M3 "시간 이탈자"//15 
#define M4 "헌츠맨 : 윈터스 워"//12 
#define M5 "독수리 에디"//12 
#define M6 "트리플 9"//18
#define M7 "캡틴 아메리카 : 시빌 워"//12
#define M8 "극장판 안녕 자두야"//All
int main()
{
	int x; int c, num;
	do {
		printf("Enter your age:\n>>");
		num = scanf("%d", &x);
		while (num == 0)
		{
			while ((c = getchar()) != EOF && c != '\n'); 
			printf("Enter your age:\n>>"); 
			num = scanf("\n%d", &x);
		}

		if (x < 12 && x > 0)
				{
				printf("Your age is %d\nYou can see the movie is as follows.\n", x);
				printf("%s,%s\n",M2,M8);
				}
		else if (x >= 12 && x < 15)
				{
				printf("Your age is %d\nYou can see the movie is as follows.\n", x);
				printf("%s,%s,%s,%s,%s\n", M2, M4, M5, M7, M8);
				}
		else if (x >= 15 && x < 18)
				{
				printf("Your age is %d\nYou can see the movie is as follows.\n", x);
				printf("%s,%s,%s,%s,%s,%s,%s", M1, M2, M3, M4, M5, M7, M8);
				}
		else if (x >= 18)
				{
				printf("Your age is %d\nYou can see the movie is as follows.\n", x);
				printf("%s,%s,%s,%s,%s,%s,%s,%s\n", M1, M2, M3, M4, M5, M6, M7, M8);
				}
	} while (x <= 0);
	return 0;
}