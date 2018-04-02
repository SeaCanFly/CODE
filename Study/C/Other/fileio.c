#include <stdio.h>
int main()
{
	FILE* f1;
	f1 = fopen("D:/Temp/C/dev c++/doc/a.txt", "r");
	printf("%d\n", f1);

	
	char M[100] = { 0 };
	fread(M, sizeof(char), 100, f1);
	printf("%s\n", M);


	fread(M, sizeof(char), 3, f1);
	printf("%s\n", M);
/*	int c;

	while ((c=fgetc(f1))!= EOF)
	{
		printf("%c\n", c);
	}*/
	fclose(f1);

	return 0;
}
