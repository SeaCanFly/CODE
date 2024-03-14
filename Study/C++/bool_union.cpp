#include<stdio.h>
#include <stdlib.h>
union test
{
	unsigned char mybool;
	struct bits
	{
		unsigned char a1:1;
		unsigned char a2:1;
		unsigned char a3:1;
		unsigned char a4:1;
		unsigned char a5:1;
		unsigned char a6:1;
		unsigned char a7:1;
		unsigned char a8:1;
	}bit;
};
struct state
{
	unsigned char b:1;
};
int main()
{
	state s;
	s.b=0;
	printf("%d\n",sizeof(s));
	printf("%d\n",s.b);
	s.b=1;
	printf("%d\n",s.b);
	union test m;
	m.mybool=0;
	printf("%d\n",m.mybool);
	m.bit.a2=1;
		printf("%d\n",m.mybool);
	system("pause");
	return 0;
}
