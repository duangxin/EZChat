#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();


private slots:
    void on_closeButton_clicked();  //最小化

    void on_minimizeButton_clicked();   //关闭窗口

    void on_confirmBtn_clicked();   //注册确认

    void on_backBtn_clicked();      //返回

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
