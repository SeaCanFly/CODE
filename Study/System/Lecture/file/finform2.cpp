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
   insa man[5]={    {"성윤정", 20, "서울"}, 
                     {"전혜영", 30, "부산"},
                     {"이은정", 24, "대구"},
                     {"오경주", 34, "서울"},
                     {"채제원", 25, "마산"}
                };
  ofstream fout;      
  fout.open("insa.bin"); 

  fout.write((char *)man, sizeof(insa)*5);

  fout.close();
}
