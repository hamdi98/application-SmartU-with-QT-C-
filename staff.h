#ifndef STAFF_H
#define STAFF_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "personne.h"
#include "demande.h"
#include "recu.h"

class Staff: public Personne
{
public:
    Staff();
    ~Staff();
    void repondre(int id, bool rep, QString daterep);
    void ajouter();
    void modifier();
    void supprimer();
    void setdep(QString dep){departement=dep;}
private:
    QString departement;
};

#endif // STAFF_H
