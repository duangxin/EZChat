#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Controller/servercontroller.h"
#include "Utilities/record.h"
#include "DataBase/mysqlhelper.h"

#include <QTcpServer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //一有日志写入就更新界面
    connect(Record::getRecord(), &Record::readyShowContent, this, &MainWindow::showLog);
    //日志更新光标移动到最底部
    connect(ui->textBrowser, &QTextEdit::cursorPositionChanged, this, &MainWindow::scrollToBottom);

    ServerController::getCtrlInstance()->getServerInstance()->start(6666);

    //连接Mysql
    auto dbHelper = MySqlHelper::GetInstance();
    if (dbHelper->connect("localhost", "ezchat_server", "root", "djx030712")) {
        dbHelper->initTables();
    }


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
