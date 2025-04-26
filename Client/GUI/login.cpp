#include "login.h"
#include "ui_login.h"
#include "./Utilities/movewidgetevent.h"
#include "register.h"
#include "Controller/clientcontroller.h"
#include "GUI/tipbox.h"
#include "Network/clienthandlerreg.h"

login* login::instance = nullptr;  // 初始化静态成员
Widget* login::mw = nullptr;       // 初始化主窗口实例
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
    this->setWindowIcon(QIcon(":/img/logonbg.ico"));
    this->setWindowTitle("EZChat");
    //给edit左侧添加图标
    ui->accountEdit->addAction(QIcon(":/img/account.png"),QLineEdit::LeadingPosition);
    ui->pswEdit->addAction(QIcon(":/img/password.png"),QLineEdit::LeadingPosition);
    ui->pswEdit->setEchoMode(QLineEdit::Password);

    connect((loginHandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::LOGIN_SUCCESS),
            &loginHandler::loginSuccessful,
            this,
            &login::showlogSuccessful
            );
    connect((loginHandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::LOGIN_ERROR),
            &loginHandler::loginFailed,
            this,
            &login::showlogFailed
            );
}

login::~login()
{
    delete ui;
    instance = nullptr;  // 析构时清除指针
}

login* login::getInstance(QWidget* parent)
{
    if (!instance) {
        instance = new login(parent);
    }
    return instance;
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
    Register::getInstance()->show();
    this->close();
}

//登录btn
void login::on_loginBtn_clicked()
{
    //通信函数
    quint32 id = ui->accountEdit->text().toUInt();
    QString pw = ui->pswEdit->text();
    ClientController::getClientInstance()->requestLogin(id, pw);
}

Widget* login::GetMainWindowInstance(){
    if(mw == nullptr){
        mw = new Widget;
    }
    return mw;
}

//登陆成功，进入主界面
void login::showlogSuccessful(UserInfo info)
{
    GetMainWindowInstance()->setUserInfo(info);
    GetMainWindowInstance()->show();
    this->close();
}

void login::showlogFailed()
{
    TipBox* box = new TipBox;
    QString str1 = "登录失败!";
    QString str2 = "账号或密码错误";
    box->setTip(str1+"\n"+str2);
    box->exec();
}

