#include "changeavatar.h"
#include "ui_changeavatar.h"
#include <QFileDialog>
#include "Network/clienthandlerreg.h"
#include "tipbox.h"

changeAvatar* changeAvatar::instance = nullptr;
changeAvatar::changeAvatar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::changeAvatar)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground); // 设置透明背景
    this->setWindowFlags(Qt::FramelessWindowHint);     // 设置无边框窗口

}

changeAvatar::~changeAvatar()
{
    delete ui;
}


changeAvatar *changeAvatar::getInstance(QWidget *parent)
{
    if (!instance) {
        instance = new changeAvatar(parent);
    }
    return instance;
}


void changeAvatar::on_closeButton_clicked()
{
    this->close();
}

void changeAvatar::on_chooseButton_clicked()
{
    QString startDir = QCoreApplication::applicationDirPath(); // 获取当前程序路径
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("选择头像"),
        startDir, // 这里改成程序运行路径
        tr("图片文件 (*.png *.jpg *.jpeg *.bmp *.gif)")
        );

    if (!fileName.isEmpty()) {
        qDebug() << "选择的头像路径:" << fileName;
        ui->lineEdit->setText(fileName);
        ui->lineEdit->setCursorPosition(0);
    } else {
        qDebug() << "用户取消了选择头像。";
    }
}


void changeAvatar::on_modifyButton_clicked()
{
    QString newAvatar = ui->lineEdit->text();
    TipBox* box = new TipBox(this);
    if(newAvatar != ""){
        ClientController::getClientInstance()->requestModifyAvatar(newAvatar);
        box->setTip("修改成功!");
        box->centerToParent();
        box->exec();
        this->close();
    }else{
        box->setTip("未选择任何图片!");
        box->centerToParent();
        box->exec();
    }
}




