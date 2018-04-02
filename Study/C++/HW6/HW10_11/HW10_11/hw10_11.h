#pragma once
#include<iostream>
#include<string>
using namespace std;
class Book
{
	string ms_year;
	string ms_author;
	string ms_bookname;
public:
	Book() :ms_author(""), ms_bookname(""), ms_year("") {}
	void setYear(string s_year) {ms_year = s_year;}
	void setAuthor(string s_author) { ms_author = s_author; }
	void setBookName(string s_bookname) { ms_bookname = s_bookname; }
	string getYear() { return ms_year; }
	string getAuthor() { return ms_author; }
	string getBookName() { return ms_bookname; }
};