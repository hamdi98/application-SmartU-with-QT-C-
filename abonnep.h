#ifndef ABONNEP_H
#define ABONNEP_H
#include <QString>
#include <QSqlQueryModel>
class abonneP
{

private:
    QString prenom;
    QString nom;
    QString ID;

public:
    abonneP();
    abonneP(QString,QString);
    QString get_nom();
    QString get_prenom();
    int get_ID();
    void set_nom(QString val) { nom = val; }
    void Set_prenom(QString val) { prenom = val; }
    void set_ID(int val){ID=val;}
    bool ajouter();
  bool  modifier(QString id);
    bool supprimer(QString );
    QSqlQueryModel * afficher();
    QSqlQuery afficherAbo(QString nom);
    bool rechercheID(QString ID);

};

#endif // ABONNEP_H
