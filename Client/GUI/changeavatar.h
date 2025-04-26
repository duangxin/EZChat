#ifndef CHANGEAVATAR_H
#define CHANGEAVATAR_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QToolButton>
#include "Controller/clientcontroller.h"

namespace Ui {
class changeAvatar;
}
class changeAvatar : public QWidget
{
    Q_OBJECT

public:
    explicit changeAvatar(QWidget *parent = nullptr);
    ~changeAvatar();
    static changeAvatar* getInstance(QWidget* parent = nullptr);  // 获取唯一实例

private slots:

    void on_closeButton_clicked();

    void on_chooseButton_clicked();

    void on_modifyButton_clicked();

private:
    Ui::changeAvatar *ui;
    static changeAvatar* instance;

};

#endif // CHANGEAVATAR_H
