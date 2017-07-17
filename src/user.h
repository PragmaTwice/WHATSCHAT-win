#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>
#include <QtNetwork/QtNetwork>
#include <QJsonDocument>

struct user_error
{
    const enum {
        network_error = 1,
        server_error,
        json_parse_error
    } tag;
    const QString reason;

    user_error(decltype(tag) _tag,const QString& _reason):tag(_tag),reason(_reason){}

};

class user
{
    static const char* const apiKey;
    static const char* const apiUrl;

    QString user_name;
    uint user_certify;

    QString temp_key;

private:
    static QJsonDocument post(const QByteArray& data);
    uint create(const QString& _user_name,const QDateTime& _expire_date);
    bool login(const QString& _user_name, const uint &_user_certify);

    friend QDebug operator << (QDebug debugOut, const user& _user);

public:
    user(const QString& _user_name,const QDateTime& _expire_date);
    user(const QString& _user_name, const uint &_user_certify);

    const QString& get_name() const;
    uint get_certify() const;

    static bool is_exist(const QString& _user_name);
};

QDebug operator << (QDebug debugOut, const user& _user);

#endif // USER_H
