#pragma once
#include<string>

using namespace std;
class CBook
{
public:
	int id;
	string author;
	string title;
	string year;
	int count;
public:
	CBook(int i, string au, string t, string y, int c){
		author = au.c_str();
		title = t.c_str();
		year = y.c_str();
		count = c;
		id = i;
	}
	CBook() {}
	~CBook(){}
};

