#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(this,SIGNAL(ALLFINISH()),SLOT(requestOfflineMsg()));
    // 第一个参数是设置无边框。第二个参数是允许任务栏按钮右键菜单，第三个参数是允许最小化与还原
    //this->setAttribute(Qt::WA_TranslucentBackground); // 设置透明背景
    this->setWindowFlags(Qt::FramelessWindowHint);     // 设置无边框窗口

}

Widget::~Widget()
{
    delete ui;
}
