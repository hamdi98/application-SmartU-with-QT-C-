#include "recu.h"

Recu::Recu()
{

}

Recu::~Recu()
{

}

bool Recu::creerrecu()
{
    QSqlQuery q;
    q.prepare("INSERT INTO RECU(IDRECU,QTERECU,IDMAT,CINN,DATERECU) "
               "VALUES(?,?,?,?,TO_DATE(?,'DD/MM/YYYY'))");
    q.addBindValue(IDRecu);
    q.addBindValue(qteRecu);
    q.addBindValue(IDMat);
    q.addBindValue(CINN);
    q.addBindValue(date);
    return q.exec();
}
