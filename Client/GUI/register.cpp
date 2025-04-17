#include "register.h"
#include "ui_register.h"
#include "./Utilities/movewidgetevent.h"
#include "login.h"
#include "GUI/tipbox.h"
#include "Controller/clientcontroller.h"
#include "Network/clienthandlerreg.h"

Register* Register::instance = nullptr;
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
    this->setWindowIcon(QIcon(":/img/logonbg.ico"));
    this->setWindowTitle("EZChat");
    //给edit左侧添加图标
    ui->accountEdit->addAction(QIcon(":/img/account.png"),QLineEdit::LeadingPosition);
    ui->pswEdit->addAction(QIcon(":/img/password.png"),QLineEdit::LeadingPosition);
    ui->re_pswEdit->addAction(QIcon(":/img/password.png"),QLineEdit::LeadingPosition);
    ui->pswEdit->setEchoMode(QLineEdit::Password);
    ui->re_pswEdit->setEchoMode(QLineEdit::Password);
    connect((registerHandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::REGISTER_SUCCESS),
            &registerHandler::registerSuccessful,
            this,
            &Register::showregSuccessful
            );
    connect((registerHandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::REGISTER_ERROR),
            &registerHandler::registerFailed,
            this,
            &Register::showregFailed
            );

}

Register::~Register()
{
    delete ui;
    instance = nullptr;
}

Register* Register::getInstance(QWidget* parent)
{
    if (!instance) {
        instance = new Register(parent);
    }
    return instance;
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
    TipBox* box = new TipBox;
    if(ui->pswEdit->text() != ui->re_pswEdit->text())
    {
        QString str1 = "注册失败!";
        QString str2 = "两次输入密码不同!";
        box->setTip(str1+"\n"+str2);
        box->exec();//仅能操作当前窗口
    }
    else if(ui->pswEdit->text() == "")
    {
        QString str1 = "注册失败!";
        QString str2 = "密码不能为空!";
        box->setTip(str1+"\n"+str2);
        box->exec();
    }
    else
    {
        //发送
        QString username=ui->accountEdit->text();
        QString pwd=ui->pswEdit->text();
        //登录请求交给controller
        ClientController::getClientInstance()->requestRegister(username,pwd);
    }
}


//注册转回登录界面
void Register::on_backBtn_clicked()
{
    login::getInstance()->show();
    this->close();
}

void Register::showregSuccessful(UserInfo info)
{
    auto* box = new TipBox();
    //auto* box = new TipBox(this);
    QString str1 = "注册成功!";
    QString str2 = QString("您的专属ID为[%1]").arg(info.getID());
    box->setTip(str1+"\n"+str2);
    box->exec();
    login::getInstance()->show();
    this->close();

}

void Register::showregFailed()
{
    TipBox* box = new TipBox;
    QString str1 = "注册失败!";
    QString str2 = "请稍后重试";
    box->setTip(str1+"\n"+str2);
    box->exec();
}

