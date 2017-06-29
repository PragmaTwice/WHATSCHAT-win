#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWin>
#include <QPropertyAnimation>
#include "waitinganime.h"
#include "messagebar.h"
#include "buttonedit.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void usernameButtonClicked(bool);

private:
    Ui::Widget *ui;
    WaitingAnime* loginingAnime;
    MessageBar* msgBar;
    ButtonEdit* usernameCol;

    void editMove(int duration, QMargins margins);
};

#endif // WIDGET_H
