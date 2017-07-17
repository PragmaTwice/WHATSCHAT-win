#include "buttondateedit.h"

ButtonDateEdit::ButtonDateEdit(const QRect &geom, const QIcon &buttonImg, const QDateTime &_startTime, const QDateTime &_endTime,const QColor& selectorColor, QWidget *parent, const QString &placeholdText):
    ButtonEdit(geom,buttonImg,parent,placeholdText),
    dateTimeSelector(_startTime,_endTime,this)
{
    dateTimeSelector.setGeometry(width()*0.2,height(),width()*0.6,width()*0.6);
    setGeometry(geometry() + QMargins(0,0,0,width()*0.6));


    dateTimeSelector.setStyleSheet(QString("QDial {background : %1}").arg(selectorColor.name()));

    connect(&dateTimeSelector,SIGNAL(sliderMoved(int)),this,SLOT(dialMoved(int)));
}

void ButtonDateEdit::setStartEndDateTime(const QDateTime &startTime, const QDateTime &endTime)
{
    dateTimeSelector.setStartDateTime(startTime);
    dateTimeSelector.setEndDateTime(endTime);
}

QDateTime ButtonDateEdit::dateTime()
{
    return dateTimeSelector.dateTime();
}

void ButtonDateEdit::dialMoved(int)
{
    setEditText(dateTimeSelector.dateTime().toString("yyyy-MM-dd hh:mm"));
}

DateTimeDial::DateTimeDial(const QDateTime &_startTime, const QDateTime &_endTime, QWidget *parent):
    QDial(parent),
    startTime(_startTime),
    endTime(_endTime)
{
    if(startTime >= endTime) throw DateTimeDialException("startTime >= endTime");

    setMinimum(startTime.toTime_t());
    setMaximum(endTime.toTime_t());
    setValue(startTime.toTime_t());
}

void DateTimeDial::setStartDateTime(const QDateTime &_startTime)
{
    if(startTime >= endTime) throw DateTimeDialException("startTime >= endTime");

    startTime = _startTime;
    setMinimum(startTime.toTime_t());
    setValue(startTime.toTime_t());
}

void DateTimeDial::setEndDateTime(const QDateTime &_endTime)
{
    if(startTime >= endTime) throw DateTimeDialException("startTime >= endTime");

    endTime = _endTime;
    setMaximum(endTime.toTime_t());
}

const QDateTime &DateTimeDial::startDateTime()
{
    return startTime;
}

const QDateTime &DateTimeDial::endDateTime()
{
    return endTime;
}

bool DateTimeDial::setDateTime(const QDateTime &wantedDateTime)
{
    if(wantedDateTime>=startTime && wantedDateTime<=endTime)
    {
        setValue(wantedDateTime.toTime_t());
        return true;
    }
    else return false;
}

QDateTime DateTimeDial::dateTime()
{
    return QDateTime::fromTime_t(value());
}
