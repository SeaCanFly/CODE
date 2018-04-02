#include<iostream>
#include<string>
#include<time.h>
using namespace std;
struct Person
{
	string name;
	string id;
	string email;
	string add_time;
	string str;
	void togeter()
	{
		str = name + ' ' + id + ' ' + email + ' ' + add_time;
	}
	void input()
	{
		cout << "input name:";
		cin >> name;
		cout << "input id:";
		cin >> id;
		cout << "input email:";
		cin >> email;	
		time_t now;
		time(&now);
		add_time=ctime(&now);
		togeter();
	}
};
int main()
{

	FILE* fp=0;
	Person a;
	a.input();

	fp=fopen("address.dat", "a");
	//fwrite(a.str.c_str(), 1, strlen(a.str.c_str()), fp);	
	fputs(a.str.c_str(), fp);
	fclose(fp);

	fp = fopen("address.dat", "rb");
	int c = 0;
	while ((c = fgetc(fp)) != EOF)
	{
		printf("%c", c);
	}
	fclose(fp);
	return 0;
}