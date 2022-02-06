#ifndef ABONNEMENT_H
#define ABONNEMENT_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
class Abonnement
{
public:
    Abonnement();
    ~Abonnement();
    void creer();
    void modifier();
    void supprimer();
    void Setid(QString x){IDAbonne=x;}
    void Settype(QString x){Type=x;}
    void Setcine(QString x){cine=x;}
private:
    QString IDAbonne;
    QString Type;
    QString cine;
};

#endif // ABONNEMENT_H
