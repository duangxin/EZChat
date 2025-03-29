#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    login w;
    w.setWindowIcon(QIcon(":/img/logonbg.ico"));
    w.setWindowTitle("EZChat");
    w.show();
    return a.exec();
}
