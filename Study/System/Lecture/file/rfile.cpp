#include <iostream>
#include <fstream>
using namespace std;

void main( )
{
	char ch;

	ifstream fin; 

	fin.open("c:\\cppwork\\ch14\\14_5\\teat.dat");

	if(fin.fail()){
		cout<<"���� ���¿� �����߽��ϴ�."<<endl;
		return;
	}

	while( fin.get(ch) )
	   cout.put(ch);

	fin.close();
}

