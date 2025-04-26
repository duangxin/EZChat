#include "changename.h"
#include "ui_changename.h"
#include "Network/clienthandlerreg.h"
#include "tipbox.h"

changeName* changeName::instance = nullptr;
changeName::changeName(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::changeName)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground); // 设置透明背景
    this->setWindowFlags(Qt::FramelessWindowHint);     // 设置无边框窗口

}

changeName::~changeName()
{
    delete ui;
}


changeName *changeName::getInstance(QWidget *parent)
{
    if (!instance) {
        instance = new changeName(parent);
    }
    return instance;
}


void changeName::on_closeButton_clicked()
{
    this->close();
}

void changeName::on_modifyButton_clicked()
{
    QString newName = ui->lineEdit->text();
    TipBox* box = new TipBox(this);
    if(newName != ""){
        ClientController::getClientInstance()->requestModifyUserName(newName);
        box->setTip("修改成功!");
        box->centerToParent();
        box->exec();
        this->close();
    }else{
        box->setTip("昵称不能为空!");
        box->centerToParent();
        box->exec();
    }
}

