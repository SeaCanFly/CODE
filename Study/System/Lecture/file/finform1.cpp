#include <iostream>
#include <fstream>
using namespace std;

struct insa{
	char name[20];
	int age;
	char address[20];
};

void main( )
{
	insa man[5]={{"������", 20, "����"}, 
	{"������", 30, "�λ�"},
		{"������", 24, "�뱸"},
		{"������", 34, "����"},
	{"ä����", 25, "����"}};

  ofstream fout;      
  fout.open("insa.dat"); 

  for(int i=0; i<5; i++)
    fout<<man[i].name<<"  "<<man[i].age<<"  "<<man[i].address<<endl;

  fout.close();
}
