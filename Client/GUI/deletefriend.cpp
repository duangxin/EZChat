#include "deletefriend.h"
#include "ui_deletefriend.h"
#include "Network/clienthandlerreg.h"
#include "tipbox.h"

deleteFriend* deleteFriend::instance = nullptr;
deleteFriend::deleteFriend(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::deleteFriend)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground); // 设置透明背景
    this->setWindowFlags(Qt::FramelessWindowHint);     // 设置无边框窗口
    connect( (deleteFriendHandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::DELETE_FRIEND_SUCCESS),
            &deleteFriendHandler::readyShowResult,this, [this](Msg msg) {
                QString tip;
                UserInfo u = UserInfo::fromQByteArray(msg.getContent());
                switch (msg.getType()) {
                case MsgType::DELETE_FRIEND_SUCCESS:
                    tip = "好友关系已取消!";
                    ClientController::getClientInstance()->dynamicRemoveFriend(u);
                    break;
                case MsgType::DELETE_FRIEND_ERROR_NOFRIEND:
                    tip = "你与对方不是好友!";
                    break;
                default:
                    tip = "删除好友失败!";
                    break;
                }
                TipBox* box = new TipBox(this);
                box->setTip(tip);
                box->centerToParent();
                box->exec();
            });
}

deleteFriend::~deleteFriend()
{
    delete ui;
}

deleteFriend *deleteFriend::getInstance(QWidget *parent)
{
    if (!instance) {
        instance = new deleteFriend(parent);
    }
    return instance;
}

void deleteFriend::on_closeButton_clicked()
{
    this->close();
}

void deleteFriend::on_deleteButton_clicked()
{
    quint32 id = ui->lineEdit->text().toUInt();
    ClientController::getClientInstance()->requestDeleteFriend(id);
}

