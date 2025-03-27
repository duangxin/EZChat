#include "widget.h"
#include "ui_widget.h"
#include <QButtonGroup>
#include <QStackedWidget>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , isDragging(false)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground); // 设置透明背景
    this->setWindowFlags(Qt::FramelessWindowHint);     // 设置无边框窗口

//对主界面初始化，各个部件样式进行排版美化放在.ui实现，designer里面能立马看到，更加方便
    // ui->centralwidget->setStyleSheet("QWidget#centralwidget{background-color:rgb(255, 255, 255);border-radius:15px;}");
    // ui->closeButton->setStyleSheet("QToolButton{color:rgb(0,0,0);border-style:none;}"
    //                                "QToolButton::hover{color:rgb(255,255,255);background-color:rgba(255, 56, 56, 150);"
    //                                "border-top-right-radius:15px;}");
    // ui->minimizeButton->setStyleSheet("QToolButton{color:rgb(0,0,0);border-style:none;}"
    //                                   "QToolButton::hover{color:rgb(255,255,255);background-color: rgba(203, 203, 203, 150);}");
    // 创建 QButtonGroup
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true); // 互斥模式（保证只能选中一个）

    // 添加按钮到组
    buttonGroup->addButton(ui->chatListBT, 0);
    buttonGroup->addButton(ui->friendsListBT, 1);

    // 连接按钮点击事件，切换界面
    connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, [this, buttonGroup]() {
                int index = buttonGroup->checkedId();  // 获取当前选中的按钮 ID
                //ui->centralwidget.s  // 切换界面
            });

    // 默认选中第一个按钮
    ui->addFriendBT->setChecked(true);
}

Widget::~Widget()
{
    delete ui;
}
//关闭窗口
void Widget::on_closeButton_clicked()
{
    this->close();
}

//窗口最小化
void Widget::on_minimizeButton_clicked()
{
    this->showMinimized();
}

//监听左键按下，计算鼠标相对于窗口左上角的位置
void Widget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastMousePos = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }

}

//监听移动，使窗口跟随鼠标拖动
void Widget::mouseMoveEvent(QMouseEvent *event) {
    //是否包含左键
    if (isDragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - lastMousePos);
        event->accept();
    }
}

//监听释放，拖动结束
void Widget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
        event->accept();
    }
}

