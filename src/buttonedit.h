#ifndef BUTTONEDIT_H
#define BUTTONEDIT_H

#include <QLineEdit>
#include <QPushButton>
#include <QPropertyAnimation>


class ButtonEdit : public QWidget
{
    Q_OBJECT

    QLineEdit edit;
    QPushButton button;

    QPropertyAnimation* anime;

    bool isProcessing;

    QRect beginEditGeom;
    QRect endEditGeom;

public:
    explicit ButtonEdit(const QRect &geom, const QIcon &buttonImg, QWidget *parent = nullptr, const QString& placeholdText = "");

    const QLineEdit& refEdit();
    const QPushButton& refButton();

    ~ButtonEdit();

signals:
    void buttonClicked(bool);

private slots:
    void slot_buttonClicked(bool);
    void setFinalStatus();

public slots:
    void clickedProcessEnd();
};

#endif // BUTTONEDIT_H
