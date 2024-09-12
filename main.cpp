#include "startwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWindow startWindow;
    startWindow.show();
    return a.exec();
}
