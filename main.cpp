#include "mainwindow.h"
#include "logger.h"
#include <QApplication>

extern Logger logger("log.txt");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logger.log(Logger::INFO, "The program is running");
    MainWindow w;
    w.show();
    return a.exec();
}
