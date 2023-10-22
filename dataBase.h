#ifndef DATABASE_H
#define DATABASE_H

#include <QVariant>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>


class DataBase;

class DataBaseDestroyer
{
    private:
        DataBase * dataBasePointer;
    public:
        ~DataBaseDestroyer() {
            delete dataBasePointer;
        }
        void initialize(DataBase * p){dataBasePointer = p;}
};


class DataBase
{
    private:
        static DataBase * p_instance;
        static DataBaseDestroyer destroyer;
        static QSqlDatabase db;
    protected:
        DataBase(){
            p_instance->db = QSqlDatabase::addDatabase("QSQLITE");
            p_instance->db.setDatabaseName("C:\\nahimov_exam\\Test.db");

            if(!p_instance->db.open())
                qDebug()<<p_instance->db.lastError().text();


        }
        DataBase(const DataBase& ) = delete;
        DataBase& operator = (DataBase &) = delete;
        ~DataBase() {db.close();}

        friend class DataBaseDestroyer;
    public:
        static DataBase* getInstance(){
            if (!p_instance)
            {
                p_instance = new DataBase();

                destroyer.initialize(p_instance);
            }
            return p_instance;
        }
        QByteArray auth(QString log, QString pass,int desc) {

            QSqlQuery query;
            query.prepare("SELECT * FROM user where log = :login and password = :password and status = :status" );
            query.bindValue(":login", log);
            query.bindValue(":password", pass);
            query.bindValue(":status", 0);
            query.exec();
            if (query.next()){
                qDebug()<<log;
                query.exec("update user set status = '" +QString::number(desc)+"' where log = '"+log+"'" );
                return "auth_true";
            }
            else{
                return "auth_false";
            }
        }
        QByteArray reg(QString log, QString pass, QString mail)
        {
            QSqlQuery query;
            query.prepare("SELECT * FROM user where log = :login" );
            query.bindValue(":login", log);
            query.exec();
            if (query.next()){
                return "reg_false";
            }
            else{
                qDebug()<<log;
                query.prepare("INSERT INTO user (log, password, email, status) VALUES (:login, :password, :email, 0)");
                query.bindValue(":login", log);
                query.bindValue(":password", pass);
                query.bindValue(":email", mail);
                query.exec();
                return "reg_true";
            }
        }
        QByteArray start_time(QString time, int soc_desc) {

            QSqlQuery query;
            if(!query.next()){
                return "start_false";
            }
            query.exec("update user set start_time = '" +time+"' where status = '"+QString::number(soc_desc)+"'");
            qDebug() << query.next();
            return "start_true";
        }
        QByteArray finish_time(QString time, int soc_desc) {
            QStringList data_time = time.trimmed().split(QLatin1Char('_'));
            qDebug() << data_time;
            int hour1 = data_time.front().toInt();
            data_time.pop_front();
            int minute1 = data_time.front().toInt();
            data_time.pop_front();
            int second1 = data_time.front().toInt();

            QSqlQuery query;
            query.prepare("SELECT start_time FROM user where status = :stat");
            query.bindValue(":stat", soc_desc);
            query.exec();
            query.first();
            qDebug() << query.first();
            QString value = query.value(0).toString();
            qDebug() << value;
            if(!query.next()){
                return "finish_err";
            }
            if(!query.first()){
                return "finish_reerr";
            }
            QStringList data_time1 = value.trimmed().split(QLatin1Char('_'));
            qDebug()<<data_time1;
            int hour2 = data_time1.front().toInt();
            data_time1.pop_front();
            int minute2 = data_time1.front().toInt();
            data_time1.pop_front();
            int second2 = data_time1.front().toInt();

            int res = (60 * 60 * hour1 + 60 * minute1 + second1) - (60 * 60 * hour2 + 60 * minute2 + second2);
            QString result_time = QString::number(res);
            query.exec("update user set finish_time = '" +result_time+"' where status = '"+0+"'");

            qDebug() << query.next();
            return "finish_true";
        }
        static QString sendQuerry(QString str){return "dfgh";}
};
/*
DataBase * DataBase::p_instance;
DataBaseDestroyer DataBase::destroyer;
QSqlDatabase DataBase::db;
*/
#endif // DATABASE_H
