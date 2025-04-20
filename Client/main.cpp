#include "GUI/login.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Widget *w =new Widget;w->show();

    login::getInstance()->show();

    return a.exec();
}
