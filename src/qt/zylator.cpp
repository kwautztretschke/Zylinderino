#include <QApplication>

#include "qt/mainwindow.h"
#include "qt/qzylinder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	QZylinder z(&w);
    w.show();
    return a.exec();
}
