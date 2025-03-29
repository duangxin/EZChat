#include "widget.h"
#include "ui_widget.h"
#include "./Utilities/movewidgetevent.h"
#include <QButtonGroup>
#include <QStackedWidget>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //安装事件过滤器，可以拖动界面
    moveWidgetEvent *moveFilter = new moveWidgetEvent(this);
    this->installEventFilter(moveFilter);

    this->setAttribute(Qt::WA_TranslucentBackground); // 设置透明背景
    this->setWindowFlags(Qt::FramelessWindowHint);     // 设置无边框窗口
    //对主界面初始化，各个部件样式进行排版美化放在.ui实现，designer里面能立马看到，更加方便

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

