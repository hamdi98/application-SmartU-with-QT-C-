#include "produit.h"
#include "connection.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
Produit::Produit()
{
    PrixProduit="";
    IDProduit="";
    qteProduit=0;
    DateProduit="";
}

Produit::Produit(QString IDProduit,int qteProduit,QString PrixProduit, QString DateProduit,long IDBuvette ): Buvette(IDBuvette)
{
    this->IDProduit=IDProduit;
    this->PrixProduit=PrixProduit;
    this->qteProduit=qteProduit;
    this->DateProduit=DateProduit;
}

QSqlQueryModel* Produit::afficherBuvette()
{
    QSqlQuery q;
    QString c = QString::number(get_IDBuvette());
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT from PRODUIT ");
    qDebug()<< q.exec();
    qDebug()<< q.first();
    return (model);
}

void Produit::ajouterProduit()
{
  QSqlQuery q;
  QString c = QString::number(get_IDBuvette());
  q.prepare("insert into PRODUIT (IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT,IDBUVETTE) VALUES (?,?,?,?,?)");
  q.addBindValue(get_IDProduit());
  q.addBindValue(get_qteProduit());
  q.addBindValue(get_DateProduit());
  q.addBindValue(get_PrixProduit());
  q.addBindValue(c);

  q.exec();
}

void Produit::modifierProduit()
{
   QSqlQuery q;
   q.prepare( "update PRODUIT set QTEPRODUIT=(?),DATEPRODUIT=(?), PRIXPRODUIT=(?) where IDPRODUIT=(?)");
   q.addBindValue(get_qteProduit());
   q.addBindValue(get_DateProduit());
   q.addBindValue(get_PrixProduit());
   q.addBindValue(get_IDProduit());
   q.exec();
}

void Produit::supprimerProduit()
{
    QSqlQuery q;
    q.prepare("delete from PRODUIT where IDPRODUIT=(?)");
    q.addBindValue(get_IDProduit());
    q.exec();
}
