#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    srand(QApplication::applicationPid());

    MainWindow w;
    w.show();

    return a.exec();
}
