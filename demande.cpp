#include "demande.h"

Demande::Demande()
{

}

Demande::~Demande()
{

}

bool Demande::creerdemande()
{
    QSqlQuery q;
    q.prepare("INSERT INTO DEMANDE(IDDEMANDE,QTEDEMANDE,IDMAT,CINN,DATEDEM) "
              "VALUES(?,?,?,?,TO_DATE(?,'DD/MM/YYYY'))");
    q.addBindValue(IDDemande);
    q.addBindValue(qteDemande);
    q.addBindValue(IDMat);
    q.addBindValue(CINN);
    q.addBindValue(date);
    return q.exec();
}

void Demande::afficher()
{
    qDebug() << "Affichage Demande : ";
    qDebug() << "----------------------";
    qDebug() << IDDemande;
    qDebug() << qteDemande;
    qDebug() << IDMat;
    qDebug() << CINN;
    qDebug() << date;
    qDebug() << "----------------------";
}

void Demande::annuler()
{
    QSqlQuery q;
    q.prepare("DELETE FROM DEMANDE WHERE IDDEMANDE = ?");
    q.addBindValue(IDDemande);
    q.exec();
}
