#include "emprunt.h"

Emprunt::Emprunt()
{

}

Emprunt::~Emprunt()
{

}

void Emprunt::creer()
{
    QSqlQuery *q = new QSqlQuery();
    q->prepare("INSERT INTO EMPRUNT(IDEMPRUNT,NOMLIVRE,CATEGORIE,DATEE,CINE)"
               "VALUES(?,?,?,?,?)");
    q->addBindValue(1);
    q->addBindValue(nomlivre);
    q->addBindValue(categorie);
    q->addBindValue(date);
    q->addBindValue(cin);
    q->exec();
}

void Emprunt::supprimer()
{
    QSqlQuery *q = new QSqlQuery();
    q->prepare("DELETE FROM EMPRUNT WHERE IDEMPRUNT = ?");
    q->addBindValue(IDEmprunt);
    q->exec();
    qDebug()<<IDEmprunt;
}

void Emprunt::modifier()
{
    QSqlQuery *q = new QSqlQuery();
    q->prepare("UPDATE EMPRUNT "
               "SET IDEMPRUNT=IDEMPRUNT, NOMLIVRE = ?, CATEGORIE = ?, DATEE = ?, CINE = ?"
               "WHERE IDEMPRUNT = ?");
    q->addBindValue(nomlivre);
    q->addBindValue(categorie);
    q->addBindValue(date);
    q->addBindValue(cin);
    q->addBindValue(IDEmprunt);
    q->exec();
}
