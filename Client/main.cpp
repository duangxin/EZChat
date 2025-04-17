#include "GUI/login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    login::getInstance()->show();

    return a.exec();
}
