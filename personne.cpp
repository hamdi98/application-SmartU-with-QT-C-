#include "personne.h"
#include "connection.h"

Personne::Personne()
{
    CIN="";
    Mail="";
    MDP="";
    Nom="";
    Prenom="";
    DateN="";
    Nationalite="";
}
Personne::Personne(QString CIN, QString Mail, QString MDP, QString Nom, QString Prenom, QString DateN, QString Nationalite)
{
    this->CIN=CIN;
    this->Mail=Mail;
    this->MDP=MDP;
    this->Nom=Nom;
    this->Prenom=Prenom;
    this->DateN=DateN;
    this->Nationalite=Nationalite;
}

void Personne::ajouterPersonne()
{
  QSqlQuery q;
  q.prepare("insert into PERSONNE (CIN,MAIL,MDP,NOM,PRENOM,DATEN,NATIONALITE,IDBASE) VALUES (?,?,?,?,?,?,?,?)");
  q.addBindValue(get_CIN());
  q.addBindValue(get_Mail());
  q.addBindValue(get_MDP());
  q.addBindValue(get_Nom());
  q.addBindValue(get_Prenom());
  q.addBindValue(get_DateN());
  q.addBindValue(get_Nationalite());
  q.addBindValue(1);
  q.exec();
}

void Personne::supprimerPersonne()
{
    QSqlQuery q;
    q.prepare("delete from PERSONNE where CIN=(?)");
    q.addBindValue(get_CIN());
    q.exec();
}

QSqlQueryModel* Personne::afficherPersonne()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select CIN,MAIL,MDP,NOM,PRENOM,DATEN,NATIONALITE from PERSONNE");
    return (model);
}

 void Personne::modifierPersonne()
{
    QSqlQuery q;
    q.prepare("update PERSONNE set MAIL=(?),MDP=(?),NOM=(?),PRENOM=(?),DATEN=(?),NATIONALITE=(?) where CIN=(?)");
    q.addBindValue(get_Mail());
    q.addBindValue(get_MDP());
    q.addBindValue(get_Nom());
    q.addBindValue(get_Prenom());
    q.addBindValue(get_DateN());
    q.addBindValue(get_Nationalite());
    q.addBindValue(get_CIN());
    q.exec();
}
