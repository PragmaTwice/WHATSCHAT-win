#ifndef BUTTONEDIT_H
#define BUTTONEDIT_H

#include <QLineEdit>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QVector2D>

class FocusableLineEdit : public QLineEdit
{
    Q_OBJECT

public:

    using QLineEdit::QLineEdit;

protected:

    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);

signals:

    void focusIn();
    void focusOut();

};

class ButtonEdit : public QWidget
{
    Q_OBJECT

    FocusableLineEdit edit;
    QPushButton button;

    QPropertyAnimation* anime;
    QPropertyAnimation* move;

    bool isProcessing;

    QRect beginEditGeom;
    QRect endEditGeom;

public:
    explicit ButtonEdit(const QRect &geom, const QIcon &buttonImg, QWidget *parent = nullptr, const QString& placeholdText = "");

    void startMoveBy(const QVector2D& vector);

    void setCanEdit(bool isCanEdit = true);
    void setEditText(const QString& text);

    const QLineEdit& refEdit();
    const QPushButton& refButton();

    ~ButtonEdit();

signals:
    void buttonClicked(bool);

    void endMoveBy();

    void focusInEdit();
    void focusOutofEdit();

private slots:
    void slot_buttonClicked(bool);

    void slot_endMoveBy();

    void setFinalStatus();

    void slot_focusInEdit();
    void slot_focusOutofEdit();

public slots:
    void clickedProcessEnd();
};

#endif // BUTTONEDIT_H
