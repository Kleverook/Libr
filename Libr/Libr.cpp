#include "Libr.h"
#include "ui_Libr.h"
#include "CLibr.h"
#include <vector>
#include<string>
#include <stdlib.h>
#include <QTextEdit>
#include<fstream>

using namespace std;
Libr::Libr(QWidget *parent)
	: QMainWindow(parent),
    ui(new Ui::LibrClass)

{
    
    ui->setupUi(this);
   
	connect(ui->search, SIGNAL(clicked()), SLOT(search_lib()));
	connect(ui->getBook, SIGNAL(clicked()), SLOT(get_book()));
	connect(ui->retBook, SIGNAL(clicked()), SLOT(return_book()));
    QStringList header;
    header << QString::fromLocal8Bit("id")
        << QString::fromLocal8Bit("Автор")
        << QString::fromLocal8Bit("Название")
        << QString::fromLocal8Bit("Год издания")
        << QString::fromLocal8Bit("В наличии");
    
    this->createUI(header);
}

void Libr::createUI(const QStringList& headers) {
	ui->tableWidget->setColumnCount(5); // Указываем число колонок
	ui->tableWidget->setRowCount(0);
	ui->tableWidget->setShowGrid(true); // Включаем сетку
	ui->tableWidget->setHorizontalHeaderLabels(headers);
	CLibr A;
	
	for (int i = 0; i < A.Lib.size(); i++) {

		char* count = new char[256];
		itoa(A.Lib[i].count, count, 10);
		//ui->tableWidget->hideColumn(0);
		ui->tableWidget->insertRow(i);
		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(tr("%1").arg(A.Lib[i].id)));
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromLocal8Bit(A.Lib[i].author.c_str())));
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit(A.Lib[i].title.c_str())));
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromLocal8Bit(A.Lib[i].year.c_str())));
		ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromLocal8Bit(count)));
	
	}
	// Ресайзим колонки по содержимому
	ui->tableWidget->resizeColumnsToContents();
}
void Libr::search_lib() {
	QString str = ui->input_search->toPlainText();
	//ui->search->setText(str);
	string text = str.toLocal8Bit().constData();
	CLibr A;
	vector <int> id;
	for (int i = 0; i < A.Lib.size(); i++) {
		if (A.Lib[i].author.find(text) != string::npos || A.Lib[i].title.find(text) != string::npos || A.Lib[i].year.find(text) != string::npos){
			id.push_back(A.Lib[i].id);

		}
	}
	CLibr B(id);
	ui->tableWidget->setRowCount(0);
	for (int i = 0; i < B.tmp.size(); i++) {

		char* count = new char[256];
		itoa(B.tmp[i].count, count, 10);
		//ui->tableWidget->hideColumn(0);
		ui->tableWidget->insertRow(i);
		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(tr("%1").arg(B.tmp[i].id)));
		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromLocal8Bit(B.tmp[i].author.c_str())));
		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit(B.tmp[i].title.c_str())));
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromLocal8Bit(B.tmp[i].year.c_str())));
		ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromLocal8Bit(count)));

	}
	// Ресайзим колонки по содержимому
	ui->tableWidget->resizeColumnsToContents();
	if (text == "") {
		QStringList header;
		header << QString::fromLocal8Bit("id")
			<< QString::fromLocal8Bit("Автор")
			<< QString::fromLocal8Bit("Название")
			<< QString::fromLocal8Bit("Год издания")
			<< QString::fromLocal8Bit("В наличии");

		this->createUI(header);
	}
}
void Libr::get_book(){
	int id = ui->idGetBook->value();
	int count = ui->countGetBook->value();
	CLibr A;
	for (int i = 0; i < A.Lib.size(); i++) {
		if (A.Lib[i].id == id) {
			if (A.Lib[i].count >= count) {
				A.Lib[i].count = A.Lib[i].count - count;
			}
		}
	}
	A.rewrite_lib();
	QStringList header;
	header << QString::fromLocal8Bit("id")
		<< QString::fromLocal8Bit("Автор")
		<< QString::fromLocal8Bit("Название")
		<< QString::fromLocal8Bit("Год издания")
		<< QString::fromLocal8Bit("В наличии");

	this->createUI(header);

}
void Libr::return_book(){
	int id = ui->idRetBook->value();
	int count = ui->countRetBook->value();
	CLibr A;
	for (int i = 0; i < A.Lib.size(); i++) {
		if (A.Lib[i].id == id) {
			A.Lib[i].count = A.Lib[i].count + count;
		}
	}
	A.rewrite_lib();
	QStringList header;
	header << QString::fromLocal8Bit("id")
		<< QString::fromLocal8Bit("Автор")
		<< QString::fromLocal8Bit("Название")
		<< QString::fromLocal8Bit("Год издания")
		<< QString::fromLocal8Bit("В наличии");

	this->createUI(header);
}
