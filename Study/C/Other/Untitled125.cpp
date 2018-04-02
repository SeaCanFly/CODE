#include<iostream>
#include<time.h>
using namespace std;
int main()
{
	long t=time(0);
	while(time(0)-t<5);
	
		cout<<"yes"<<endl;
	
	getchar();
	return 0;
}
