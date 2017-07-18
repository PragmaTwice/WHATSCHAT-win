#ifndef MESSAGEBAR_H
#define MESSAGEBAR_H

#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>

class MessageBar : public QLabel
{
    Q_OBJECT

    QPropertyAnimation* up_anime;
    QPropertyAnimation* down_anime;

    QTimer* timer;

public:
    explicit MessageBar(QWidget *parent, uint height);

    ~MessageBar();

signals:
    void messageInFinished();
    void messageOutFinished();

public slots:
    void messageOut();

private slots:
    void slot_messageInFinished();
    void slot_messageOutFinished();

public:
    void message(const QString& content, const QColor& back_color, const QColor& text_color = Qt::white, uint interval = 4000);

    void messageIn(const QString& content, const QColor& back_color, const QColor& text_color = Qt::white);

    void information(const QString& content, const QColor& back_color = QColor::fromRgb(58,95,205), const QColor& text_color = Qt::white, uint interval = 4000);

    void warning(const QString& content, const QColor& back_color = QColor::fromRgb(238,64,0), const QColor& text_color = Qt::white, uint interval = 4000);

};

#endif // MESSAGEBAR_H
