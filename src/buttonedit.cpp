#include "buttonedit.h"

ButtonEdit::ButtonEdit(const QRect& geom, const QIcon &buttonImg, QWidget *parent, const QString &placeholdText) :
    QWidget(parent),
    edit(this),
    button(this),
    anime(nullptr),
    move(nullptr),
    isProcessing(false)
{
    setGeometry(geom);

    beginEditGeom = QRect(0,geom.height()*0.15,geom.width()-geom.height()*1.2,geom.height()*0.7);
    endEditGeom = beginEditGeom + QMargins(0,0,height(),0);
    QRect buttonGeom(geom.width()-geom.height(),0,geom.height(),geom.height());

    edit.setGeometry(beginEditGeom);
    edit.setFont(QFont("Segoe UI Light",beginEditGeom.height()/2.5));
    edit.setPlaceholderText(placeholdText);

    button.setGeometry(buttonGeom);
    button.setIcon(buttonImg);
    button.setIconSize(button.size());
    button.setStyleSheet("QPushButton{border:0;}");

    anime = new QPropertyAnimation(&edit,"geometry");
    move = new QPropertyAnimation(this,"geometry");

    connect(&button,SIGNAL(clicked(bool)),this,SLOT(slot_buttonClicked(bool)));

    connect(&edit,SIGNAL(focusIn()),this,SLOT(slot_focusInEdit()));
    connect(&edit,SIGNAL(focusOut()),this,SLOT(slot_focusOutofEdit()));

    connect(anime,SIGNAL(finished()),this,SLOT(setFinalStatus()));
    connect(move,SIGNAL(finished()),this,SLOT(slot_endMoveBy()));
}

void ButtonEdit::startMoveBy(const QVector2D &vector)
{
    move->stop();
    move->setStartValue(geometry());
    move->setEndValue(geometry() + QMargins(vector.x(),vector.y(),0,0));
    move->setDuration(2*(vector.length()));
    move->start();
}

void ButtonEdit::setCanEdit(bool isCanEdit)
{
    edit.setReadOnly(!isCanEdit);
}

void ButtonEdit::setEditText(const QString &text)
{
    edit.setText(text);
}

const QLineEdit &ButtonEdit::refEdit()
{
    return edit;
}

const QPushButton &ButtonEdit::refButton()
{
    return button;
}

ButtonEdit::~ButtonEdit()
{
    delete anime;
    delete move;
}

void ButtonEdit::slot_buttonClicked(bool arg)
{
    edit.setReadOnly(true);
    button.setVisible(false);
    edit.clearFocus();
    isProcessing = true;

    anime->stop();
    anime->setStartValue(edit.geometry());
    anime->setEndValue(endEditGeom);
    anime->setDuration(10*(endEditGeom.width() - edit.geometry().width()));
    anime->start();

    emit buttonClicked(arg);
}

void ButtonEdit::slot_endMoveBy()
{
    emit endMoveBy();
}

void ButtonEdit::setFinalStatus()
{
    if(!isProcessing)
    {
        button.setVisible(true);
        edit.setReadOnly(false);
        edit.setFocus();
    }
    else
    {
        edit.clearFocus();
    }
}

void ButtonEdit::slot_focusInEdit()
{
    emit focusInEdit();
}

void ButtonEdit::slot_focusOutofEdit()
{
    emit focusOutofEdit();
}

void ButtonEdit::clickedProcessEnd()
{
    isProcessing = false;

    anime->stop();
    anime->setStartValue(edit.geometry());
    anime->setEndValue(beginEditGeom);
    anime->setDuration(10*(edit.geometry().width() - beginEditGeom.width()));
    anime->start();
}

void FocusableLineEdit::focusInEvent(QFocusEvent *e)
{
    emit focusIn();
}

void FocusableLineEdit::focusOutEvent(QFocusEvent *e)
{
    emit focusOut();
}
