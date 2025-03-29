#include "login.h"
#include "ui_login.h"
#include "./Utilities/movewidgetevent.h"
#include "register.h"

Widget * login:: mw = NULL;
login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
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

}

login::~login()
{
    delete ui;
}

//关闭窗口
void login::on_closeButton_clicked()
{
    this->close();
}

//窗口最小化
void login::on_minimizeButton_clicked()
{
    this->showMinimized();
}

//跳转注册界面
void login::on_registerBtn_clicked()
{
        //请求交给controller
    Register *w = new Register;
    w->show();
    this->close();
}

//登录btn
void login::on_loginBtn_clicked()
{
        //请求交给controller
    Widget *mainw = GetMainWindowInstance();
    mainw->show();
    this->close();
}

Widget* login::GetMainWindowInstance(){
    if(mw == nullptr){
        mw = new Widget;
    }
    return mw;
}

