#ifndef PLACE_H
#define PLACE_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include"abonnep.h"
class place
{
public:
    QString num;
    QString ID;
    QString get_num();
    QString get_ID();
    void set_num(QString val) { num = val; }
   place();
   place(QString,QString);
    bool ajouter( );
  bool  modifier( QString num,QString id);
    bool supprimer(QString );
    QSqlQueryModel * afficher();

};

#endif // PLACE_H
