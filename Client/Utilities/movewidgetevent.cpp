#include "movewidgetevent.h"
#include <QWidget>

moveWidgetEvent::moveWidgetEvent(QObject *parent)
    : QObject{parent}
    , isDragging(false)
{}

bool moveWidgetEvent::eventFilter(QObject *obj, QEvent *event) {
    QWidget *widget = qobject_cast<QWidget *>(obj);  // 将 obj 动态转换为 QWidget
    if (!widget) return false;  // 如果 obj 不是 QWidget，则不处理


    //static_cast<QMouseEvent *>(event)将QEvent* 转换成 QMouseEvent*  因为handle参数是mouseEvent，该函数的event是QEvent
    if (event->type() == QEvent::MouseButtonPress) {
        handleMousePress(static_cast<QMouseEvent *>(event), widget);
        return true;  // 拦截事件
    } else if (event->type() == QEvent::MouseMove) {
        handleMouseMove(static_cast<QMouseEvent *>(event), widget);
        return true;
    } else if (event->type() == QEvent::MouseButtonRelease) {
        handleMouseRelease(static_cast<QMouseEvent *>(event));
        return true;
    }
    return QObject::eventFilter(obj, event);  // 继续传递事件
}

// 监听左键按下，记录鼠标相对于窗口的位置
void moveWidgetEvent::handleMousePress(QMouseEvent *event, QWidget *widget) {
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastMousePos = event->globalPosition().toPoint() - widget->frameGeometry().topLeft();
        event->accept();    //已经处理，不用再传递
    }
}

// 监听鼠标移动，拖动窗口
void moveWidgetEvent::handleMouseMove(QMouseEvent *event, QWidget *widget) {
    if (isDragging && (event->buttons() & Qt::LeftButton)) {
        widget->move(event->globalPosition().toPoint() - lastMousePos);
        event->accept();
    }
}

// 监听鼠标释放，停止拖动
void moveWidgetEvent::handleMouseRelease(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
        event->accept();
    }
}

