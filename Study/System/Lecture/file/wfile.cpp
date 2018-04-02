#include <iostream>
#include <fstream>
using namespace std;

void main( )
{
	char ch;

	ofstream fout; 

	fout.open("teat.dat");

	while( cin.get(ch) )
	   fout.put(ch);

	fout.close();
}

