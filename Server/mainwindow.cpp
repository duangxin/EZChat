#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Controller/servercontroller.h"
#include "Utilities/record.h"

#include <QTcpServer>
#include <QNetworkInterface>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ServerController::getServerInstance()->start(6666);

    //一有日志写入就更新界面
    connect(Record::getRecord(), &Record::readyShowContent, this, &MainWindow::showLog);

    //日志更新光标移动到最底部
    connect(ui->textBrowser, &QTextEdit::cursorPositionChanged, this, &MainWindow::scrollToBottom);

    //显示可用的IP
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback())
            Record::getRecord()->writeRecord( "服务器可连接 IP：" + address.toString());
    }

      //DataDB::GetInstance();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//界面添加一条日志
void MainWindow::showLog(QString str)
{

    ui->textBrowser->append(str);
}

//光标到底部
void MainWindow::scrollToBottom()
{

    QTextCursor cursor =  ui->textBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);  //光标移动到末尾
    ui->textBrowser->setTextCursor(cursor);

}
