#include "DIPtest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DIPtest w;
	w.show();
	return a.exec();
}
