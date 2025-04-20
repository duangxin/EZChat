#include "widget.h"
#include "ui_widget.h"
#include "./Utilities/movewidgetevent.h"
#include "addfriend.h"
#include "frdmanege.h"
#include "tipbox.h"
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

    /*初始化*/
    //单例控制器
    ClientController * client = ClientController::getClientInstance();

    ui->friendList->hide();
    ui->chatList->hide();
    ui->initList->hide();
    currentList = ui->initList;
    currentList->show();
    //好友管理按键的菜单
    frdManageMenu = new QMenu(ui->funcFrame);
    frdManageMenu->addAction("添加好友",this,SLOT(on_addFriend_clicked()));
    frdManageMenu->addAction("删除好友",this,SLOT(onAddFriend()));
    frdManageMenu->addAction("验证消息",this,SLOT(on_friendRequest_clicked()));
    ui->frdManageBT->setPopupMode(QToolButton::InstantPopup);
    ui->frdManageBT->setMenu(frdManageMenu);
    connect((addFriendHandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::REQUEST_ADD_FRIEND),
            &addFriendHandler::readyShowFriendRequest, this, &Widget::handleFriendRequest);

    //设置按键的菜单
    settingMenu = new QMenu(ui->funcFrame);
    settingMenu->addAction("修改头像", this, SLOT(onChangeAvatar()));
    settingMenu->addAction("修改昵称", this, SLOT(onChangeNickname()));
    ui->settingBT->setPopupMode(QToolButton::InstantPopup);
    ui->settingBT->setMenu(settingMenu);


    // 创建 QButtonGroup
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true); // 互斥模式（保证只能选中一个）
    // 添加按钮到组
    buttonGroup->addButton(ui->chatListBT, 0);
    buttonGroup->addButton(ui->friendsListBT, 1);

    //聊天好友信息
    auto chatFriendLabel= new QLabel(ui->dialogFrame);
    chatFriendLabel->setGeometry(20, 5, 560, 40);
    chatFriendLabel->setText("dd [576513]");
    chatFriendLabel->setStyleSheet("color:rgb(41,97,253); padding: 5px;"
                                   "border: 1px solid rgb(41,97,253);border-radius:15px;");
    // 设置字体大小
    QFont font = chatFriendLabel->font();
    font.setPointSize(14); // 设置字体大小为14
    chatFriendLabel->setFont(font);

    // 聊天记录区域：ScrollArea
    QScrollArea* chatScrollArea = new QScrollArea(ui->dialogFrame);
    chatScrollArea->setGeometry(0, 50, 600, 400);
    chatScrollArea->setWidgetResizable(true);

    // 聊天内容容器（真正承载消息的）
    QWidget* chatContentWidget = new QWidget();
    QVBoxLayout* chatLayout = new QVBoxLayout(chatContentWidget);
    chatLayout->setAlignment(Qt::AlignTop); // 从上往下排列
    chatLayout->setSpacing(10);
    chatLayout->setContentsMargins(10, 10, 10, 10);

    // 设置容器到 scrollArea 里
    chatScrollArea->setWidget(chatContentWidget);

    {
        QWidget* msgWidget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(msgWidget);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(10);

        QLabel* avatar = new QLabel();
        avatar->setFixedSize(40, 40);
        avatar->setPixmap(QPixmap(":/img/logo.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        QLabel* msgLabel = new QLabel("你好duangxin");
        msgLabel->setWordWrap(true);
        msgLabel->setStyleSheet(
            "background-color: #E0F0FF;"
            "border-radius: 15px;"
            "padding: 8px 12px;"    //字体距离气泡
            "font-size: 14px;"
            "color: #000000;"
            );
        msgLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

        layout->addWidget(avatar);
        layout->addWidget(msgLabel);
        layout->addStretch();

        chatLayout->addWidget(msgWidget);
    }

    // ---------- 自己发的消息 ----------
    {
        QWidget* msgWidget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(msgWidget);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(10);

        QLabel* avatar = new QLabel();
        avatar->setFixedSize(40, 40);
        avatar->setPixmap(QPixmap(":/img/logo.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        QLabel* msgLabel = new QLabel("你好dd");
        msgLabel->setWordWrap(true);
        msgLabel->setStyleSheet(
            "background-color: #D1F2C9;"
            "border-radius: 15px;"
            "padding: 8px 12px;"
            "font-size: 14px;"
            "color: #000000;"
            );
        msgLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

        layout->addStretch();
        layout->addWidget(msgLabel);
        layout->addWidget(avatar);

        chatLayout->addWidget(msgWidget);
    }


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
    //同意刷新列表
    connect( (addFriendAnswerhandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::REQUEST_ADD_FRIEND_AGREED),
            &addFriendAnswerhandler::sigAddFriendSuccessful,
            this,&Widget::getFriendInfo);
    connect( (addFriendAnswerhandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::REQUEST_ADD_FRIEND_AGREED),
            &addFriendAnswerhandler::sigAddFriendSuccessful,
            this,&Widget::getFriendInfo);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initUserInfo(UserInfo info)
{
    this->id = info.getID();
    this->name = info.getName();
    this->pwd = info.getPwd();
    this->avatarPath = info.getAvatarName();
}

void Widget::setUserInfo()
{
    //头像
    ui->avatarBT->setIcon(QIcon(avatarPath));

    //用户名
    ui->nameLabel->setText("用户名:"+name);
    //用户id
    ui->idLabel->setText("ID:"+QString::number(id));
}

void Widget::getFriendInfo()
{
    // 1. 获取好友列表
    auto friendList = ClientController::getClientInstance()->getFriendList();
    if (!friendList) {
        qDebug() << "[getFriendInfo] 获取好友列表失败（friendList 是空指针）";
        return;
    }

    // 2. 清空原来的布局（如果存在）
    QLayout* oldLayout = ui->friendList->layout();
    if (oldLayout) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            QWidget* widget = item->widget();
            if (widget) {
                delete widget;
            }
            delete item;
        }
        delete oldLayout;
    }

    // 3. 创建新布局
    QVBoxLayout* layout = new QVBoxLayout(ui->friendList);
    layout->setContentsMargins(3, 3, 3, 3);
    qDebug() << "[getFriendInfo] 获取好友数量：" << friendList->size();
    // 4. 创建好友按钮并添加进布局
    for (const auto& userInfo : *friendList) {
        QToolButton* btn = new QToolButton(ui->friendList);
        btn->setFixedSize(235, 50);
        btn->setText(userInfo.getName());
        btn->setObjectName(QString::number(userInfo.getID()));
        btn->setIcon(QIcon(userInfo.getAvatarName().isEmpty() ? ":/img/justin.jpg" : userInfo.getAvatarName()));
        btn->setIconSize(QSize(40, 40));
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btn->setStyleSheet("QToolButton{color: black; font-size: 16px; text-align: left;}");

        layout->addWidget(btn);
        // 点击事件：在这里打开聊天窗口或切换聊天页面
        connect(btn, &QToolButton::clicked, this, [=]() {
            qDebug() << "点击了好友：" << userInfo.getName() << " ID:" << userInfo.getID();
            //在这里调用打开聊天界面函数

        });
    }
    layout->addStretch();
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


void Widget::on_friendsListBT_clicked()
{
    getFriendInfo();

    currentList->hide();
    currentList = ui->friendList;
    currentList->show();
}


void Widget::on_chatListBT_clicked()
{
    currentList->hide();
    currentList = ui->chatList;
    currentList->show();
}

//
void Widget::on_addFriend_clicked()
{
    addFriend::getInstance(this)->show();
}

void Widget::handleFriendRequest(UserInfo info)
{
    pendingRequests.enqueue(info); // 缓存到请求队列中
    frdManege* window = frdManege::getInstance(this);
    window->setSender(info);
    window->setReceiverId(ClientController::getClientInstance()->getMyInfo().getID());
}
void Widget::on_friendRequest_clicked()
{    if (pendingRequests.isEmpty()) {
        TipBox* box = new TipBox;
        box->setTip("当前没有新的好友请求!");
        box->exec();
        return;
    }
    // 每次只弹一个
    pendingRequests.dequeue();
    frdManege::getInstance(this)->show();

}
