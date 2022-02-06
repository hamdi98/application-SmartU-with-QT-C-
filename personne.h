#ifndef PERSONNE_H
#define PERSONNE_H
#include <QString>
#include <iostream>
#include <QSqlQueryModel>
using namespace std;

class Personne
{ protected:
    QString CIN;
    QString Mail;
    QString MDP;
    QString Nom;
    QString Prenom;
    QString DateN;
    QString Nationalite;
public:
    Personne();
    Personne(QString, QString, QString, QString, QString, QString, QString);

 void set_CIN(QString CIN){this->CIN=CIN;}
 void set_Mail(QString Mail){this->Mail=Mail;}
 void set_MDP(QString MDP){this->MDP=MDP;}
 void set_Nom(QString Nom){this->Nom=Nom;}
 void set_Prenom(QString Prenom){this->Prenom=Prenom;}
 void set_DateN(QString DateN){this->DateN=DateN;}
 void set_Nationalite(QString Nationalite){this->Nationalite=Nationalite;}

 QString get_CIN(){return CIN;}
 QString get_Mail(){return Mail;}
 QString get_MDP(){return MDP;}
 QString get_Nom(){return Nom;}
 QString get_Prenom(){return Prenom;}
 QString get_DateN(){return DateN;}
 QString get_Nationalite(){return Nationalite;}

 void ajouterPersonne();
 void supprimerPersonne();
 QSqlQueryModel* afficherPersonne();
 void modifierPersonne();


};
#endif // PERSONNE_H
