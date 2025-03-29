#ifndef MOVEWIDGETEVENT_H
#define MOVEWIDGETEVENT_H

#include <QObject>
#include <QEvent>
#include <QMouseEvent>

//监听鼠标事件，实现拖动界面

class moveWidgetEvent : public QObject
{
    Q_OBJECT
public:
    explicit moveWidgetEvent(QObject *parent = nullptr);

protected:
    //事件过滤器
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    bool isDragging; //是否在拖动
    QPoint lastMousePos;//鼠标位置
    //实现可以拖动
    void handleMousePress(QMouseEvent *event, QWidget *widget);
    void handleMouseMove(QMouseEvent *event, QWidget *widget);
    void handleMouseRelease(QMouseEvent *event);

signals:

};

#endif // MOVEWIDGETEVENT_H
