#include <QtGui/QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //DialogSetting* setting = new DialogSetting(&w);
    //setting->show();
    return a.exec();
}
