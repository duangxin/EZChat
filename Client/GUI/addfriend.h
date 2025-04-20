#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QToolButton>
#include "Controller/clientcontroller.h"

namespace Ui {
class addFriend;
}

class addFriend : public QWidget
{
    Q_OBJECT

public:
    explicit addFriend(QWidget *parent = nullptr);
    ~addFriend();
    static addFriend* getInstance(QWidget* parent = nullptr);  // 获取唯一实例

private slots:
    void on_closeButton_clicked();

    void on_addButton_clicked();
    void showAddFriendSuccess();
    void showAddFriendFailed(MsgType type);
private:
    Ui::addFriend *ui;
    static addFriend* instance;

};

#endif // ADDFRIEND_H
