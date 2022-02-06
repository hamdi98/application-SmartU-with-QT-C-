#include "buvette.h"
#include <QSqlQuery>
#include "connection.h"
#include <QSqlQueryModel>
Buvette::Buvette()
{
    IDBuvette=0;
}

Buvette::Buvette(long IDBuvette)
{
    this->IDBuvette=IDBuvette;
}


