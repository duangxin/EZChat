#include "tipbox.h"
#include "ui_tipbox.h"
#include <QToolButton>

TipBox::TipBox(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TipBox)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground); // 设置透明背景
    this->setWindowFlags(Qt::FramelessWindowHint);     // 设置无边框窗口
    this->setWindowTitle("tipBox!");

    // 创建一个 QFrame 作为背景
    QFrame *background = new QFrame(this);
    background->resize(300, 150);
    background->move(this->rect().center() - background->rect().center());//位于界面中间
    background->setStyleSheet("background-color:white; border-radius: 15px;");

    tip = new QLabel(background);
    tip->setAlignment(Qt::AlignCenter);
    tip->setGeometry(50, 30, 200, 50);

    QToolButton *btnOK = new QToolButton(background);
    btnOK->setText("确定");
    btnOK->setGeometry(110, 100, 80, 30);
    btnOK->setStyleSheet("QToolButton{"
                         "background-color: #0078D7; color: white; border-radius: 5px;}"
                         "QToolButton::hover{"
                        "background-color:#00aaff;}");
    connect(btnOK, &QToolButton::clicked, this, &QDialog::accept);

}

TipBox::~TipBox()
{
    delete ui;
}

void TipBox::setTip(QString str)
{
    tip->setText(str);
}
