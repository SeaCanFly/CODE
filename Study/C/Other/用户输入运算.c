#include<stdio.h>

int main(void)
{
	float a, b, r;
	char c;
	printf("first num\n>");
	scanf("%f", &a);//���뻺�������¼�س���
	getchar();      //ȡ�������뻺�����Ļس���
	printf("+-*/\n>");
	scanf("%c", &c);
	printf("second num\n>");
	scanf("%f", &b);
	switch (c)
	{
	case '+':r = a + b;
		break;
	case '-':r = a - b;
		break;
	case '*':r = a*b;
		break;
	case '/':r = a / b;
		break;
	default:r = 0;
	}
	printf("%.2f%c%.2f=%.2f\n", a, c, b, r);
	return 0;
}
