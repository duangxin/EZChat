#include "widget.h"
#include "ui_widget.h"
#include "./Utilities/movewidgetevent.h"
#include "Controller/clientcontroller.h"
#include <QButtonGroup>
#include <QStackedWidget>
#include <QVBoxLayout>

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
    this->setWindowIcon(QIcon(":/img/logonbg.ico"));
    this->setWindowTitle("EZChat");
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



    //初始化
    ClientController * client = ClientController::getClientInstance();
    //聊天的发送框
    txt= new QTextEdit(ui->dialogFrame);
    txt->setGeometry(0, 430, 600, 130);
    txt->setStyleSheet("QTextEdit{background-color:rgb(255,255,255);border:none;"
                       "border-bottom-right-radius:15px;border-top:1px solid rgb(41,97,253)}");


    //聊天发送按钮
    Send = new QToolButton(ui->dialogFrame);
    Send->setText("发送");
    Send->setGeometry(510,500,60,30);
    Send->setStyleSheet("QToolButton{background-color:rgb(85,170,255);color:rgb(41,97,253);"
                        "border:1px solid rgb(41,97,253);border-radius:5px;}");
    connect(Send,SIGNAL(clicked()),this,SLOT(sendtxt()));

    QToolButton* toolbtn1 = new QToolButton(ui->listFrame);
    toolbtn1->setIconSize(QSize(40,40));
    toolbtn1->setStyleSheet("QToolButton{color:rgb(0,0,0);border:none;font-size:20px;}");
    toolbtn1->setIcon(QIcon(":/img/justin.jpg"));
    toolbtn1->setText(" 用户1");
    toolbtn1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    QToolButton* toolbtn2 = new QToolButton(ui->listFrame);
    toolbtn2->setIconSize(QSize(40,40));
    toolbtn2->setStyleSheet("QToolButton{color:rgb(0,0,0);border:none;font-size:20px;}");
    toolbtn2->setIcon(QIcon(":/img/justin.jpg"));
    toolbtn2->setText(" 用户2");
    toolbtn2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QVBoxLayout* layout = new QVBoxLayout(ui->listFrame);
    layout->addWidget(toolbtn1);
    layout->addWidget(toolbtn2);
    layout->addStretch();  // 内容自动向上对齐
    layout->setSpacing(12);  // 设置按钮之间的垂直间距为 12px

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

