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
   insa man[5]={    {"������", 20, "����"}, 
                     {"������", 30, "�λ�"},
                     {"������", 24, "�뱸"},
                     {"������", 34, "����"},
                     {"ä����", 25, "����"}
                };
  ofstream fout;      
  fout.open("insa.bin"); 

  fout.write((char *)man, sizeof(insa)*5);

  fout.close();
}
