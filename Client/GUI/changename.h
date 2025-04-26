#ifndef CHANGENAME_H
#define CHANGENAME_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QToolButton>
#include "Controller/clientcontroller.h"

namespace Ui {
class changeName;
}

class changeName : public QWidget
{
    Q_OBJECT

public:
    explicit changeName(QWidget *parent = nullptr);
    ~changeName();
    static changeName* getInstance(QWidget* parent = nullptr);  // 获取唯一实例

private slots:
    void on_closeButton_clicked();

    void on_modifyButton_clicked();

private:
    Ui::changeName *ui;
    static changeName* instance;

};

#endif // CHANGENAME_H
