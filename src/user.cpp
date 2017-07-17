#include "user.h"

const char* const user::apiKey = "vczh";
const char* const user::apiUrl = "https://c.imtwice.cn/api/chat.v170713.php";

QJsonDocument user::post(const QByteArray &data)
{
    QUrl url(user::apiUrl);
    QNetworkAccessManager manager;
    QEventLoop loop;

    QNetworkRequest request(url);
    QNetworkReply *reply = manager.post(request,data);

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QJsonDocument jsonResult;
    switch (reply->error())
    {
    case QNetworkReply::NoError:

        QJsonParseError parseErr;
        jsonResult = QJsonDocument::fromJson(reply->readAll(), &parseErr);

        if(parseErr.error != QJsonParseError::NoError)
        {
            throw user_error(user_error::json_parse_error,parseErr.errorString());

            jsonResult.setObject(QJsonObject{{"succeed",QJsonValue(false)}});
            return jsonResult;
        }
        else return jsonResult;

    default:

        int httpStatus = reply->attribute(
            QNetworkRequest::HttpStatusCodeAttribute).toInt();
        QString httpStatusMessage = reply->attribute(
            QNetworkRequest::HttpReasonPhraseAttribute).toByteArray();

        throw user_error(user_error::network_error,QString("%1:%2").arg(httpStatus).arg(httpStatusMessage));

        jsonResult.setObject(QJsonObject{{"succeed",QJsonValue(false)}});
        return jsonResult;
    }
}

uint user::create(const QString &_user_name, const QDateTime &_expire_date)
{
    QByteArray data;
    data.append(QString("key=%1&").arg(user::apiKey));
    data.append(QString("opr=create_user&"));
    data.append(QString("user_name=%1&").arg(_user_name));
    data.append(QString("expire_date=%1").arg(_expire_date.toTime_t()));

    QJsonDocument result = post(data);

    if(result.object()["succeed"].toBool())
    {
        user_name = _user_name;
        user_certify = result.object()["info"].toObject()["certify"].toInt();
        return user_certify;
    }
    else
    {
        throw user_error(user_error::server_error,result.object()["error"].toString());
        return 0;
    }
}

bool user::login(const QString &_user_name, const uint &_user_certify)
{
    QByteArray data;
    data.append(QString("key=%1&").arg(user::apiKey));
    data.append(QString("opr=login_user&"));
    data.append(QString("user_name=%1&").arg(_user_name));
    data.append(QString("user_certify=%1").arg(_user_certify));

    QJsonDocument result = post(data);

    if(result.object()["succeed"].toBool())
    {
        user_name = _user_name;
        user_certify = _user_certify;
        temp_key = result.object()["info"].toObject()["user_key"].toString();
        return true;
    }
    else
    {
        QString error = result.object()["error"].toString();
        throw user_error(user_error::server_error,error);
        return false;
    }
}

user::user(const QString &_user_name, const QDateTime &_expire_date)
{
    create(_user_name,_expire_date);
    login(user_name,user_certify);
}

user::user(const QString &_user_name, const uint &_user_certify)
{
    login(_user_name,_user_certify);
}

uint user::get_certify() const
{
    return user_certify;
}

const QString& user::get_name() const
{
    return user_name;
}

bool user::is_exist(const QString &_user_name)
{
    try
    {
        user(_user_name,1);
    }
    catch(const user_error& err)
    {
        if(err.tag == user_error::server_error)
        {
            if(err.reason == "certify error")
                return true;
            else if(err.reason == "user not existed" || err.reason == "user expire date")
                return false;
            else
            {
                throw err;
                return false;
            }
        }
        else
        {
            throw err;
            return false;
        }
    }

    return false;
}

QDebug operator <<(QDebug debugOut, const user &_user)
{
#if defined QT_DEBUG
    debugOut << QString("user(%1){user_name:%2,user_certify:%3,temp_key:%4}")
                .arg((const int)&_user)
                .arg(_user.user_name)
                .arg(_user.user_certify)
                .arg(_user.temp_key);
#endif
    return debugOut;
}
