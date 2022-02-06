#include "abonnep.h"
#include <QDebug>
#include<QSqlQuery>

abonneP::abonneP()
{
ID="";
nom="";
prenom="";

}
abonneP::abonneP(QString nom,QString prenom)
{
    this->nom=nom;
    this->prenom=prenom;
}

  /*  QString abonneP::get_nom(){return  nom;}
    QString abonneP::get_prenom(){return prenom;}
    int abonneP::get_ID(){return  ID;}*/



bool abonneP::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO PARKING (NOM, PRENOM) "
                        "VALUES (:nom,:prenom)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);

    return    query.exec();
}

bool abonneP::supprimer(QString  ID)
{
    QSqlQuery query;

    query.prepare("Delete from PARKING where IDPARKING = :id ");
    query.bindValue(":id", ID);

    return  query.exec();
}



QSqlQueryModel * abonneP::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select  * from PARKING ");

        return model;
}

    bool abonneP ::modifier(QString id)
{

        QSqlQuery q;
        q.prepare("update PARKING set NOM=:nom,PRENOM=:prenom where IDPARKING=:id" );


        q.bindValue(":nom",nom);
        q.bindValue(":prenom",prenom);
        q.bindValue(":id",id);

        return q.exec();
}

QSqlQuery abonneP::afficherAbo(QString id)
{
    QSqlQuery qry;

    qry.prepare("SELECT * from PARKING where IDPARKING = :id" );
    qry.bindValue(":id",id);
    return qry;
}

bool abonneP::rechercheID(QString id)
{
    QSqlQuery qry;

    qry.prepare("SELECT * from PARKING where IDPARKING = :id" );
    qry.bindValue(":id",id);
    return qry.exec();
}
