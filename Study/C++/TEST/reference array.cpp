#include<iostream>
using namespace std;
template<int T>
int add(int (&p)[T])
{
	int i_sum = 0;
	for (int i = 0; i < T; i++)
	{
		p[i] = i;
	}
	for (int i = 0; i < T; i++)
	{
		i_sum += p[i];
	}
	return i_sum;
}
template<typename U,typename T>
T mul(U a, T b)
{
	return a*b;
}
int(& re())[10]
{
	int sia_r[10] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		sia_r[i] = i;
	}
	return sia_r;
}
int main()
{
	int ia_check[100] = { 0 };
	cout << add(ia_check)<<endl;
	for (int i = 0; i < 10; i++)
	{
		cout << re()[i] << endl;
	}
	cout << mul(2.9, 3) << endl;
	return 0;
}