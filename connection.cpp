#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("Fares");
    db.setPassword("Admin");
    if (db.open())
    {
        test=true;
        qDebug() <<"Connected!";
    }
    else
    {
        qDebug() <<"Error!";
    }
    return  test;
}
