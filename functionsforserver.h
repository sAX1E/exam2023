#ifndef FUNCTIONSFORSERVER_H
#define FUNCTIONSFORSERVER_H
#include <QString>
#include "dataBase.h"
#include <QStringList>
/**
 * \brief parsing - функция, которая по введенному названию
 * и параметрам функции возращает результат.
 * \param [in] data_from_client - строка, которая приходит от клиента
 * в формате....
 * \return Возвращает результат работы функции, которая была подана на вход.
 *
 * \example указать_файл.txt
 */
QByteArray parsing (QString data_from_client, int soc_desc);

QByteArray auth(QString log, QString pass, int soc_desc);

QByteArray reg(QString log, QString pass,QString mail);
QByteArray start_time(QString time, int soc_desc);
QByteArray finish_time(QString time, int soc_desc);
#endif
// FUNCTIONSFORSERVER_H
