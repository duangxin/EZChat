#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMouseEvent>
#include "widget.h"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    static Widget* GetMainWindowInstance();  // 获取 MainWindow 实例
    ~login();



private slots:
    void on_closeButton_clicked();  //最小化

    void on_minimizeButton_clicked();   //关闭窗口

    void on_registerBtn_clicked();  //跳转注册界面

    void on_loginBtn_clicked();     //登录btn

private:
    Ui::login *ui;
    static Widget* mw;  // 静态指针，指向唯一的widget主窗口实例

};

#endif // LOGIN_H
