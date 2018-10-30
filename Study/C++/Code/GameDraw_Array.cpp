#include<cstdio>
#include<string>
#include<Windows.h>
using namespace std;
#define LMAX 20
int main()
{
	char m[LMAX] = { 0 };
	int bullet = 0;
	bool direction = 0;
	while (1)
	{
		memset(m, ' ', LMAX);
		if (direction == 0)
		{
			m[bullet] = '>';
			bullet++;
			if (bullet == LMAX-1)
			{
				direction = 1;
				bullet = LMAX - 2;
			}
		}

		else
		{
			m[bullet] = '<';
			bullet--;
			if (bullet < 0)
			{
				direction = 0;
				bullet = 0;
			}
		}
		m[LMAX - 1] = NULL;
		printf("%s\r", m);
		Sleep(200);
	}
	return 0;
}
