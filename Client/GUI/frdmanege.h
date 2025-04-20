#ifndef FRDMANEGE_H
#define FRDMANEGE_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QToolButton>
#include "Controller/clientcontroller.h"

namespace Ui {
class frdManege;
}

class frdManege : public QWidget
{
    Q_OBJECT

public:
    explicit frdManege(QWidget *parent = nullptr);
    ~frdManege();
    static frdManege* getInstance(QWidget* parent = nullptr);  // 获取唯一实例
    void setSender(UserInfo sender);
    void setReceiverId(quint32 receiverId);
    UserInfo getSender();
    quint32 getReceiverId();

private slots:

    void on_closeButton_clicked();

    void on_agreeButton_clicked();

    void on_refuseButton_clicked();

private:
    Ui::frdManege *ui;
    static frdManege* instance;
    UserInfo Sender;
    quint32 receiverId;
};

#endif // FRDMANEGE_H
