#ifndef EMPRUNT_H
#define EMPRUNT_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
class Emprunt
{
public:
    Emprunt();
    ~Emprunt();
    void creer();
    void supprimer();
    void modifier();
    void Setid(QString id){IDEmprunt=id;}
    void Setlivre(QString nom){nomlivre=nom;}
    void Setcat(QString cat){categorie=cat;}
    void Setdate(QString d){date=d;}
    void Setcin(QString cine){cin=cine;}
private:
    QString IDEmprunt;
    QString nomlivre;
    QString categorie;
    QString date;
    QString cin;
};

#endif // EMPRUNT_H
