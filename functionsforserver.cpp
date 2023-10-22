#include "functionsforserver.h"

QByteArray parsing (QString data_from_client,int desc)
{
    if(data_from_client.contains('\\'))
    {
        QStringList data_from_client_list = data_from_client.trimmed().split(QLatin1Char('\\'));
        QString login, pass, mail, time;
        qDebug() << data_from_client_list;
        if(data_from_client_list.front() == "auth"){
            data_from_client_list.pop_front();
            login = data_from_client_list.front();
            data_from_client_list.pop_front();
            pass = data_from_client_list.front();
            return auth(login, pass, desc);
        }else if(data_from_client_list.front() == "reg"){
            data_from_client_list.pop_front();
            login = data_from_client_list.front();
            data_from_client_list.pop_front();
            pass = data_from_client_list.front();
            data_from_client_list.pop_front();
            mail = data_from_client_list.front();
            return reg(login, pass, mail);
        }else if(data_from_client_list.front() == "start"){
            data_from_client_list.pop_front();
            time = data_from_client_list.front();
            return start_time(time, desc);
        }else if(data_from_client_list.front() == "finish"){
            data_from_client_list.pop_front();
            time = data_from_client_list.front();
            return finish_time(time, desc);
        }
    }else{
        return data_from_client.toUtf8();
    }

}
QByteArray auth(QString log, QString pass, int soc_desc)
{
     return DataBase::getInstance()->auth(log, pass, soc_desc);
}

QByteArray start_time(QString time, int soc_desc)
{
     return DataBase::getInstance()->start_time(time, soc_desc);
}

QByteArray finish_time(QString time, int soc_desc)
{
     return DataBase::getInstance()->finish_time(time, soc_desc);
}

QByteArray reg(QString log, QString pass,QString mail)
{
    return DataBase::getInstance()->reg(log, pass, mail);
}
