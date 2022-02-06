#include "abonnement.h"

Abonnement::Abonnement()
{

}

Abonnement::~Abonnement()
{

}

void Abonnement::creer()
{
    QSqlQuery q;
    q.prepare("INSERT INTO Abonnement(IDABONNEMENT,CINE,TYPEABONNE)"
              "VALUES(?,?,?)");
    q.addBindValue(IDAbonne);
    q.addBindValue(cine);
    q.addBindValue(Type);
    q.exec();
}

void Abonnement::modifier()
{
    QSqlQuery q;
    q.prepare("UPDATE ABONNEMENT "
              "SET CINE = ?, TYPEABONNE = ?"
              "WHERE IDABONNEMENT = ?");
    q.addBindValue(cine);
    q.addBindValue(Type);
    q.addBindValue(IDAbonne);
    q.exec();
}

void Abonnement::supprimer()
{
    QSqlQuery q;
    q.prepare("DELETE FROM ABONNEMENT WHERE IDABONNEMENT = ?");
    q.addBindValue(IDAbonne);
    q.exec();
}
