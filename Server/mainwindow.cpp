#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Controller/servercontroller.h"

#include <QTcpServer>
#include <QNetworkInterface>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ServerController::getServerInstance()->start(6666);
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback())
            qDebug() << "服务器可连接 IP：" << address.toString();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
