#ifndef DEMANDE_PARKING_H
#define DEMANDE_PARKING_H
#include <QString>
#include <QSqlQueryModel>

class demande_parking
{
public:
    demande_parking();
    demande_parking(QString nom,QString prenom,QString CIN,QString EMAIL,QString date);
    bool supprimer (QString );
    QSqlQueryModel * afficher();


    bool ajouter();

private:
    QString nom,prenom,CIN,EMAIL,date;
};
#endif // DEMANDE_PARKING_H
