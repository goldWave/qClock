#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Jimbo Ltd");
    a.setOrganizationDomain("qtrac.eu");
    a.setQuitOnLastWindowClosed(false);
    MainWindow w;
    w.show();
    return a.exec();
}
