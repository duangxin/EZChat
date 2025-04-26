#ifndef DELETEFRIEND_H
#define DELETEFRIEND_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QToolButton>
#include "Controller/clientcontroller.h"

namespace Ui {
class deleteFriend;
}

class deleteFriend : public QWidget
{
    Q_OBJECT

public:
    explicit deleteFriend(QWidget *parent = nullptr);
    ~deleteFriend();
    static deleteFriend* getInstance(QWidget* parent = nullptr);  // 获取唯一实例


private slots:
    void on_closeButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::deleteFriend *ui;
    static deleteFriend* instance;
};

#endif // DELETEFRIEND_H
