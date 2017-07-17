#ifndef BUTTONDATEEDIT_H
#define BUTTONDATEEDIT_H

#include "buttonedit.h"
#include <QDial>
#include <QDateTime>

struct DateTimeDialException
{
    const QString reason;

    DateTimeDialException(const QString& _reason): reason(_reason) {}

};

class DateTimeDial : public QDial
{
    Q_OBJECT

    QDateTime startTime;
    QDateTime endTime;

public:

    explicit DateTimeDial(const QDateTime& _startTime, const QDateTime& _endTime, QWidget* parent = nullptr);

    void setStartDateTime(const QDateTime& _startTime);
    void setEndDateTime(const QDateTime& _endTime);
    const QDateTime& startDateTime();
    const QDateTime& endDateTime();

    bool setDateTime(const QDateTime& wantedDateTime);
    QDateTime dateTime();

};

class ButtonDateEdit : public ButtonEdit
{
    Q_OBJECT

    DateTimeDial dateTimeSelector;

public:

    explicit ButtonDateEdit(const QRect &geom, const QIcon &buttonImg, const QDateTime &_startTime, const QDateTime &_endTime, const QColor &selectorColor = Qt::white, QWidget *parent = nullptr, const QString& placeholdText = "");

    void setStartEndDateTime(const QDateTime& startTime,const QDateTime& endTime);

    QDateTime dateTime();

private slots:

    void dialMoved(int value);

};

#endif // BUTTONDATEEDIT_H
