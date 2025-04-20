#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QTextEdit>
#include <QToolButton>
#include <QScrollArea>
#include <QMenu>
#include <QQueue>
#include "datamodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initUserInfo(UserInfo info); //登录用户绑定到程序
    void setUserInfo(); //显示头像和昵称和id
    void getFriendInfo(); //获取好友信息


protected:

private slots:
    void on_closeButton_clicked();  //最小化

    void on_minimizeButton_clicked();   //关闭窗口

    void on_friendsListBT_clicked();    //好友列表

    void on_chatListBT_clicked();   //聊天列表

    void on_addFriend_clicked();
    void handleFriendRequest(UserInfo info);
    void on_friendRequest_clicked();


private:
    Ui::Widget *ui;
    QQueue<UserInfo> pendingRequests;   //好友申请的队列
    QString avatarPath=":/img/justin.jpg"; //用户头像
    QString name; //用户名
    quint32 id; //用户ID
    QString pwd; // 用户密码
    QTextEdit *txt;  //文本编辑框
    QToolButton* Send;//发送按钮
    QMenu *frdManageMenu;//好友管理菜单
    QMenu *settingMenu;//设置菜单
    QFrame *currentList;
};
#endif // WIDGET_H
