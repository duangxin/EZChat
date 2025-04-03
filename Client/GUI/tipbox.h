#ifndef TIPBOX_H
#define TIPBOX_H
//该项目的各种提示框
#include <QDialog>
#include <QLabel>

namespace Ui {
class TipBox;
}

class TipBox : public QDialog
{
    Q_OBJECT

public:
    explicit TipBox(QWidget *parent = nullptr);
    ~TipBox();
    void setTip(QString str);

private:
    Ui::TipBox *ui;
    QLabel *tip;    //提示文字
};

#endif // TIPBOX_H
