#include "Libr.h"
#include "CLibr.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));

	QApplication a(argc, argv);
	CLibr A;
	Libr w;
	
	w.show();
	
	
	return a.exec();
}
