#include<iostream>
#include<string>
using namespace std;
int main()
{
	while (true)
	{
		string str;
		cout << "Enter a line(\"exit\" to exit)" << endl<<">>";
		getline(cin, str);
		if (str == "exit")
		{
			break;
		}
		else
		{
			int size = str.size()-1;
			for (size; size >= 0; size--)
			{
				cout << str.at(size);
			}
			cout << endl;
		}
	}
	return 0;
}