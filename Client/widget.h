#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>

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

protected:

private slots:
    void on_closeButton_clicked();  //最小化

    void on_minimizeButton_clicked();   //关闭窗口

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
