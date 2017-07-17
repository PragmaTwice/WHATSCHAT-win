#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWin>
#include <QPropertyAnimation>
#include "waitinganime.h"
#include "messagebar.h"
#include "buttonedit.h"
#include "buttondateedit.h"
#include "user.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

private slots:
    void usernameButtonClicked(bool);
    void colMoveEnd();

    void dateButtonClicked(bool);
    void certifyButtonClicked(bool);

    void on_backButton_clicked(bool);

private:
    Ui::LoginWidget *ui;

    WaitingAnime* loginingAnime;
    MessageBar* msgBar;

    ButtonEdit* usernameCol;
    ButtonEdit* certifyCol;
    ButtonDateEdit* dateCol;

    ButtonEdit* nowCol;

    QColor systemColor;

    void editMove(int duration, QMargins margins);
    void forceStopColProcess(ButtonEdit* const col,const QString& warningString);
    bool checkColBlank(ButtonEdit* const col,const QString& warningString);

    void nextColProcess(ButtonEdit * const nowCol, ButtonEdit * const nextCol = nullptr, const QString &infoString = "", uint interval = 4000);
    void backColProcess(ButtonEdit * const nowCol, ButtonEdit * const backCol = nullptr, const QString &infoString = "", uint interval = 4000);
};

#endif // WIDGET_H
