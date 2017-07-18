#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDialog>
#include "user.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QDialog
{
    Q_OBJECT

public:
    explicit MainWidget(user* _userPtr, QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

    user* userPtr;

};

#endif // MAINWIDGET_H
