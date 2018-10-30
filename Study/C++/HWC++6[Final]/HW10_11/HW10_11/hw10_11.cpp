/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #10_11
Visual Studio 2015
*/
#include"hw10_11.h"
#include<vector>
void searchbyauthor(vector<Book>& v,string author)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].getAuthor() == author)
		{
			cout << v[i].getYear() << ", " << v[i].getBookName() << ", " << v[i].getAuthor() << endl;
		}
	}
}
void searchbyyear(vector<Book>& v, string year)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].getYear() == year)
		{
			cout << v[i].getYear() << ", " << v[i].getBookName() << ", " << v[i].getAuthor() << endl;
		}
	}
}
int main()
{
	vector<Book>v;
	while (1)
	{
		string bookname = "";
		string author = "";
		string year = "";
		Book temp;
		cout << "Book library,year=-1 to exit." << endl;
		cout << "year>>";
		getline(cin, year);
		if (year == "-1")
		{
			break;
		}
		temp.setYear(year);
		cout << "BookName>>";
		getline(cin, bookname);
		temp.setBookName(bookname);
		cout << "Author>>";
		getline(cin, author);
		temp.setAuthor(author);
		v.push_back(temp);
	}
	string author = "";
	string year = "";
	cout << "There are " << v.size() << " books in all" << endl;
	cout << "Search by Author>>";
	getline(cin, author);
	searchbyauthor(v, author);
	cout << "Search by Year>>";
	getline(cin, year);
	searchbyyear(v, year);
	return 0;
}