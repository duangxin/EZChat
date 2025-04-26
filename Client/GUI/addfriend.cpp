#include "addfriend.h"
#include "ui_addfriend.h"
#include "Network/clienthandlerreg.h"
#include "tipbox.h"

addFriend* addFriend::instance = nullptr;
addFriend::addFriend(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::addFriend)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground); // 设置透明背景
    this->setWindowFlags(Qt::FramelessWindowHint);     // 设置无边框窗口


    connect( (addFriendAnswerhandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::REQUEST_ADD_FRIEND_AGREED),
            &addFriendAnswerhandler::sigAddFriendSuccessful,
            this, &addFriend::showAddFriendSuccess);
    connect((addFriendAnswerhandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::REQUEST_ADD_FRIEND_DECLINED),
            &addFriendAnswerhandler::sigAddFriendFailed,
            this,&addFriend::showAddFriendFailed);

    connect((addFriendAnswerhandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIENDSHIP_EXIST),
            &addFriendAnswerhandler::sigAddFriendFailed, this, [this](MsgType type) {
                QString tip;
                switch (type) {
                case MsgType::REQUEST_ADD_FRIEND_ERROR_FRIENDSHIP_EXIST:
                    tip = "您和对方已是好友!";
                    break;
                case MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_NOT_EXIST:
                    tip = "该用户不存在!";
                    break;
                case MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_OFFLINE:
                    tip = "该用户已离线!";
                    break;
                default:
                    tip = "添加好友失败!";
                    break;
                }
                TipBox* box = new TipBox(this);
                box->setTip(tip);
                box->centerToParent();
                box->exec();
            });
}

addFriend::~addFriend()
{
    delete ui;
}

addFriend *addFriend::getInstance(QWidget *parent)
{
    if (!instance) {
        instance = new addFriend(parent);
    }
    return instance;
}

void addFriend::on_closeButton_clicked()
{
    this->close();
}


void addFriend::on_addButton_clicked()
{
    quint32 id = ui->lineEdit->text().toUInt();
    ClientController::getClientInstance()->requestAddFriend(id);
}

void addFriend::showAddFriendSuccess()
{

    TipBox* box = new TipBox(this);
    box->setTip("对方通过申请!");
    box->centerToParent();
    box->exec();
    this->close();
}

void addFriend::showAddFriendFailed(MsgType type)
{
    if(type == MsgType::REQUEST_ADD_FRIEND_DECLINED){
        TipBox* box = new TipBox(this);
        box->setTip("对方拒绝申请!");
        box->centerToParent();
        box->exec();
        this->close();
    }
}

