#include "frdmanege.h"
#include "ui_frdmanege.h"
#include "Network/clienthandlerreg.h"
#include "tipbox.h"


frdManege* frdManege::instance = nullptr;
frdManege::frdManege(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frdManege)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground); // 设置透明背景
    this->setWindowFlags(Qt::FramelessWindowHint);     // 设置无边框窗口

}

frdManege::~frdManege()
{
    delete ui;
}

frdManege *frdManege::getInstance(QWidget *parent)
{
    if (!instance) {
        instance = new frdManege(parent);
    }
    return instance;
}


void frdManege::setSender(UserInfo sender)
{
    this->Sender = sender;
    ui->IDlabel->setText(QString::number(sender.getID()));

}

void frdManege::setReceiverId(quint32 receiverId)
{
    this->receiverId = receiverId;
}

UserInfo frdManege::getSender()
{
    return Sender;
}

quint32 frdManege::getReceiverId()
{
    return receiverId;
}

void frdManege::on_closeButton_clicked()
{
    this->close();
}


void frdManege::on_agreeButton_clicked()
{
    ClientController::getClientInstance()->agreeFriendRequest(Sender.getID(), receiverId);
    ClientController::getClientInstance()->dynamicAppendFriend(Sender);
    TipBox* box = new TipBox(this);
    box->setTip("您已同意!");
    box->centerToParent();
    box->exec();
    this->close();
}

void frdManege::on_refuseButton_clicked()
{
    ClientController::getClientInstance()->declineFriendRequest(Sender.getID(), receiverId);
    TipBox* box = new TipBox(this);
    box->setTip("您已拒绝!");
    box->centerToParent();
    box->exec();
    this->close();
}

