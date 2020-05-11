#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include "CBook.h"
#include <QtWidgets/QApplication>
#include <QTableWidget>
#include "Libr.h"
class CLibr :
	public CBook
{
public:
	vector<CBook> Lib, tmp;

	void get_books() {
		fstream file;
		file.open("Text.txt");
		string str, au, t, y,c;
		int count = 0;
		while (!file.eof()) {
			
			getline(file, au, '|');
			getline(file, t, '|');
			getline(file, y, '|');
			getline(file, c, '\n');
			if (Lib.size() == 0) {
				Lib.push_back(CBook(count, au,t, y, stoi(c)));
				count++;
			}
			else {
				for (int i = 0; i < Lib.size(); i++) {
					if (Lib[i].author == au && Lib[i].title == t && Lib[i].year == y) {
						Lib[i].count += stoi(c);
						i++;
					}
					else {
						Lib.push_back(CBook(count,au, t, y, stoi(c)));
						i++;
						i++;
						count++;
					}
				}
			}
			
			
		}
		file.close();
	}
	void rewrite_lib() {
		ofstream file;
		file.open("Text.txt", ios_base::trunc);
		for (int i = 0; i < Lib.size(); i++) {
			if (i != Lib.size() - 1) { 
				file << Lib[i].author << "|" << Lib[i].title << "|" << Lib[i].year << "|" << Lib[i].count << endl; 
			}
			else {
				file << Lib[i].author << "|" << Lib[i].title << "|" << Lib[i].year << "|" << Lib[i].count;
			}
		}

		file.close();
	}
	CLibr() { get_books(); 

	}
	CLibr(vector<int> id) {
		get_books();
		for (int i = 0; i < Lib.size(); i++) {
			for (auto j : id) {
				if (j == Lib[i].id) {
					tmp.push_back(Lib[i]);
				}

			}
		}
	}
};

