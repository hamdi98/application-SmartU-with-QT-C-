#ifndef PRODUIT_H
#define PRODUIT_H
#include "buvette.h"
#include <QString>
class Produit : public Buvette
{
private:
    QString IDProduit;
    int qteProduit;
    QString PrixProduit;
    QString DateProduit;
public:
    Produit();
    Produit(QString, int,QString,QString,long);


    void set_IDProduit(QString IDProduit){this->IDProduit=IDProduit;}
    void set_qteProduit(int qteProduit){this->qteProduit=qteProduit;}
     void set_PrixProduit(QString PrixProduit){this->PrixProduit=PrixProduit;}
    void set_DateProduit(QString DateProduit){this->DateProduit=DateProduit;}

    QString get_IDProduit(){return IDProduit;}
    QString get_PrixProduit(){return PrixProduit;}
    int get_qteProduit(){return qteProduit;}
    QString get_DateProduit(){return DateProduit;}

    void set_IDBuvette(long IDBuvette){this->IDBuvette=IDBuvette;}
    long get_IDBuvette(){return IDBuvette;}

    QSqlQueryModel* afficherBuvette();
    void ajouterProduit();
    void modifierProduit();
    void supprimerProduit();

};

#endif // PRODUIT_H
