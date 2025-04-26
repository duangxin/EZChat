#include "widget.h"
#include "ui_widget.h"
#include "./Utilities/movewidgetevent.h"
#include "addfriend.h"
#include "deletefriend.h"
#include "frdmanege.h"
#include "changename.h"
#include "changeavatar.h"
#include "tipbox.h"
#include "Controller/clientcontroller.h"
#include "database.h"
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
    DataBase::GetInstance();

    ui->friendList->hide();
    ui->chatList->hide();
    ui->initList->hide();
    currentList = ui->initList;
    currentList->show();
    //好友管理按键的菜单
    frdManageMenu = new QMenu(ui->funcFrame);
    frdManageMenu->addAction("添加好友",this,SLOT(on_addFriend_clicked()));
    frdManageMenu->addAction("删除好友",this,SLOT(on_deleteFriend_clicked()));
    frdManageMenu->addAction("验证消息",this,SLOT(on_friendRequest_clicked()));
    ui->frdManageBT->setPopupMode(QToolButton::InstantPopup);
    ui->frdManageBT->setMenu(frdManageMenu);
    connect((addFriendHandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::REQUEST_ADD_FRIEND),
            &addFriendHandler::readyShowFriendRequest, this, &Widget::handleFriendRequest);

    //设置按键的菜单
    settingMenu = new QMenu(ui->funcFrame);
    settingMenu->addAction("修改头像", this, SLOT(on_changeAvatar_clicked()));
    settingMenu->addAction("修改昵称", this, SLOT(on_changeName_clicked()));
    ui->settingBT->setPopupMode(QToolButton::InstantPopup);
    ui->settingBT->setMenu(settingMenu);

    // 创建 QButtonGroup
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true); // 互斥模式（保证只能选中一个）
    // 添加按钮到组
    buttonGroup->addButton(ui->chatListBT, 0);
    buttonGroup->addButton(ui->friendsListBT, 1);

    initChatArea();


    //同意刷新列表
    connect( (addFriendAnswerhandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::REQUEST_ADD_FRIEND_AGREED),
            &addFriendAnswerhandler::sigAddFriendSuccessful,
            this,&Widget::getFriendInfo);

    //修改信息的槽
    connect( (changeNameHandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::MODIFY_USERNAME_SUCCESS),
            &changeNameHandler::modifyUserNameSuccess,
            this,&Widget::setName);
    connect( (changeAvatarHandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::MODIFY_AVATAR_SUCCESS),
            &changeAvatarHandler::modifyAvatarSuccess,
            this,&Widget::setAvatar);

    //展示好友消息
    connect( (chatMsgHandler *) ClientHandlerReg::GetInstance()->getHandler(MsgType::MSG_TEXT),
            &chatMsgHandler::readyShowChatMsg,
            this,
            [this](const ChatMessage& msg) {
                showFriendMsg(msg.getContent());
                DataBase::GetInstance()->addMsg(currentChatFriend.getID(),logUser.getID(),msg.getContent());
            });
}

Widget::~Widget()
{
    delete ui;
}

// void Widget::initUserInfo(UserInfo info)
// {
//     this->logUser = info;
// }

void Widget::setUserInfo(UserInfo info)
{
    //改之前先更新信息
    this->logUser = info;
    //头像
    ui->avatarBT->setIcon(QIcon(logUser.getAvatarName()));

    //用户名
    ui->nameLabel->setText("用户名:"+logUser.getName());
    //用户id
    ui->idLabel->setText("ID:"+QString::number(logUser.getID()));
}

void Widget::setAvatar(UserInfo info)
{
    ui->avatarBT->setIcon(QIcon(info.getAvatarName()));
}

void Widget::setName(UserInfo info)
{
    ui->nameLabel->setText("用户名:"+info.getName());
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
            showChatWithFriend(userInfo);

        });
    }
    layout->addStretch();
}

void Widget::initChatArea()
{
    // 顶部聊天对象名
    chatFriendLabel = new QLabel(ui->dialogFrame);
    chatFriendLabel->setGeometry(20, 5, 560, 40);
    chatFriendLabel->setStyleSheet("color:rgb(41,97,253); padding: 5px;"
                                   "border: 1px solid rgb(41,97,253);border-radius:15px;");
    QFont font = chatFriendLabel->font();
    font.setPointSize(14);
    chatFriendLabel->setFont(font);
    chatFriendLabel->setText("请点击好友开始聊天");

    //所有消息都是往chatLayout里加的，
    //chatLayout属于chatContentWidget，
    //而chatContentWidget又被嵌入到了chatScrollArea里。
    QScrollArea* chatScrollArea = new QScrollArea(ui->dialogFrame);
    chatScrollArea->setGeometry(0, 50, 600, 400);
    chatScrollArea->setWidgetResizable(true);

    // 聊天内容布局区域，添加垂直布局chatLayout
    QWidget* chatContentWidget = new QWidget();
    chatLayout = new QVBoxLayout(chatContentWidget);
    chatLayout->setAlignment(Qt::AlignTop);
    chatLayout->setSpacing(10); //每条消息间距
    chatLayout->setContentsMargins(10, 10, 10, 10);
    chatScrollArea->setWidget(chatContentWidget);

    // 聊天输入框
    txt = new QTextEdit(ui->dialogFrame);
    txt->setGeometry(0, 440, 600, 100);
    txt->setStyleSheet("QTextEdit{background-color:rgb(255,255,255);border:none;"
                       "border-bottom-right-radius:15px;border-top:1px solid rgb(41,97,253)}");
    font = txt->font();
    font.setPointSize(14);
    txt->setFont(font);
    txt->hide();

    // 发送按钮
    Send = new QToolButton(ui->dialogFrame);
    Send->setText("发送");
    Send->setGeometry(510, 500, 60, 30);
    Send->setStyleSheet("QToolButton{background-color:rgb(85,170,255);color:rgb(41,97,253);"
                        "border:1px solid rgb(41,97,253);border-radius:8px;}");
    Send->hide();

    // 发送槽函数
    connect(Send, &QToolButton::clicked, this, &Widget::sendtxt);
}

//关闭窗口
void Widget::on_closeButton_clicked()
{
    ClientController::getClientInstance()->requestLogout(logUser.getID());
    this->close();
}

//窗口最小化
void Widget::on_minimizeButton_clicked()
{
    this->showMinimized();
}


void Widget::on_friendsListBT_clicked()
{
    ClientController::getClientInstance()->requestFriendList(this->logUser);
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

//好友管理三个控件
void Widget::on_addFriend_clicked()
{
    addFriend::getInstance(this)->show();
}
void Widget::on_deleteFriend_clicked()
{
    deleteFriend::getInstance(this)->show();
}
void Widget::on_friendRequest_clicked()
{
    // qDebug() << "Is pendingRequests empty? " << pendingRequests.isEmpty();
    // qDebug() << "Size of pendingRequests: " << pendingRequests.size();
    // for (const UserInfo& user : pendingRequests) {
    //     qDebug() << "User ID:" << user.getID() << ", Name:" << user.getName();
    // }
    if (pendingRequests.isEmpty()) {
        TipBox* box = new TipBox(ui->centralwidget);
        box->setTip("当前没有新的好友请求!");
        box->centerToParent();
        box->exec();
        return;
    }

    // 每次只弹一个
    pendingRequests.dequeue();
    frdManege::getInstance(this)->show();

}
//好友应答反馈，放到队列里面
void Widget::handleFriendRequest(UserInfo info)
{
    pendingRequests.enqueue(info); // 缓存到请求队列中
    frdManege* window = frdManege::getInstance(this);
    window->setSender(info);
    window->setReceiverId(ClientController::getClientInstance()->getMyInfo().getID());
}
//修改昵称，头像
void Widget::on_changeAvatar_clicked()
{
    changeAvatar::getInstance(this)->show();
}
void Widget::on_changeName_clicked()
{
    changeName::getInstance(this)->show();
}
//展示自己的消息
void Widget::showMyMsg(const QString& content)
{
    QWidget* msgWidget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(msgWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);

    QLabel* avatar = new QLabel();
    avatar->setFixedSize(40, 40);
    avatar->setPixmap(QPixmap(logUser.getAvatarName()).scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel* msgLabel = new QLabel(content);
    msgLabel->setWordWrap(true);
    msgLabel->setStyleSheet("background-color: #D1F2C9;"
                            "border-radius: 15px;"
                            "padding: 8px 12px;"
                            "font-size: 14px;"
                            "color: #000000;");
    msgLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    layout->addStretch();
    layout->addWidget(msgLabel);
    layout->addWidget(avatar);

    chatLayout->addWidget(msgWidget);
}
//展示好友消息
void Widget::showFriendMsg(const QString& content)
{
    QWidget* msgWidget = new QWidget(); // 放头像和消息
    QHBoxLayout* layout = new QHBoxLayout(msgWidget);   // 水平布局
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);     // 头像与消息间距

    QLabel* avatar = new QLabel();
    avatar->setFixedSize(40, 40);
    avatar->setPixmap(QPixmap(currentChatFriend.getAvatarName()).scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel* msgLabel = new QLabel(content);
    msgLabel->setWordWrap(true);
    msgLabel->setStyleSheet("background-color: #E0F0FF;"
                            "border-radius: 15px;"
                            "padding: 8px 12px;"
                            "font-size: 14px;"
                            "color: #000000;");
    msgLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    layout->addWidget(avatar);
    layout->addWidget(msgLabel);
    layout->addStretch();           // 靠左
    chatLayout->addWidget(msgWidget);
}


//发送消息
void Widget::sendtxt()
{
    QString content = txt->toPlainText().trimmed();
    if (content.isEmpty() || currentChatFriend.getID() == 0) return;

    showMyMsg(content);  // 展示自己的消息
    txt->clear();
    //sqlite保存本地消息
    DataBase::GetInstance()->addMsg(logUser.getID(),currentChatFriend.getID(),content);
    //发送到服务器
    ClientController::getClientInstance()->sendChatMessage(currentChatFriend.getID(), content);


}
//打开聊天界面
void Widget::showChatWithFriend(const UserInfo& friendInfo)
{
    currentChatFriend = friendInfo;

    // 更新顶部标签
    chatFriendLabel->setText(friendInfo.getName() + " [" + QString::number(friendInfo.getID()) + "]");
    //chatFriendLabel->show();

    // 显示输入框和按钮
    txt->show();
    Send->show();

    // 清空聊天输入框
    txt->clear();

    // 清除旧聊天记录（从chatLayout中移除所有 child）
    QLayoutItem* item;
    while ((item = chatLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    //加载聊天记录
    auto history = DataBase::GetInstance()->loadChatHistory(logUser.getID(), friendInfo.getID());
    for (const ChatMessage& msg : history) {
        if (msg.getSender() == logUser.getID())
            showMyMsg(msg.getContent());
        else
            showFriendMsg(msg.getContent());
    }


}

