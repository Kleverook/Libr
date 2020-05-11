#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Libr.h"
#include "CLibr.h"

namespace Ui {
	class Libr;
}
class Libr : public QMainWindow
{
	Q_OBJECT

public:
	Libr(QWidget *parent = Q_NULLPTR);

protected:
	Ui::LibrClass *ui;
	QPushButton* search;
	void createUI(const QStringList& headers);

private slots:
	void search_lib();
	void get_book();
	void return_book();
};
