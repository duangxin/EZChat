#include "register.h"
#include "ui_register.h"
#include "./Utilities/movewidgetevent.h"
#include "login.h"

Register::Register(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);

    //安装事件过滤器，可以拖动界面
    moveWidgetEvent *moveFilter = new moveWidgetEvent(this);
    this->installEventFilter(moveFilter);

    this->setAttribute(Qt::WA_TranslucentBackground); // 设置透明背景
    this->setWindowFlags(Qt::FramelessWindowHint);     // 设置无边框窗口
    //给edit左侧添加图标
    ui->accountEdit->addAction(QIcon(":/img/account.png"),QLineEdit::LeadingPosition);
    ui->pswEdit->addAction(QIcon(":/img/password.png"),QLineEdit::LeadingPosition);
    ui->re_pswEdit->addAction(QIcon(":/img/password.png"),QLineEdit::LeadingPosition);
}

Register::~Register()
{
    delete ui;
}



//关闭窗口
void Register::on_closeButton_clicked()
{
    this->close();
}

//窗口最小化
void Register::on_minimizeButton_clicked()
{
    this->showMinimized();
}

//注册确认
void Register::on_confirmBtn_clicked()
{
    //请求交给controller

}

//注册转回登录界面
void Register::on_backBtn_clicked()
{
        //请求交给controller
    login *w = new login;
    w->show();
    this->close();
}

