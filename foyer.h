#ifndef FOYER_H
#define FOYER_H


#include <QString>
#include <QVariant>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class Foyer
{
    QString  nom , email , id_chambre ;
    int cine ;

public:
    void  mailSent(QString);
    Foyer();
    Foyer (int , QString ,QString ,QString );
    bool ajouter () ;
    bool modifier(int , QString ,QString, QString   );
    bool supprimer(int );
    bool payer(QString  , QString );

    bool demande(int ,QString, QString ,int );
    bool supp (int );
    bool supp2 (int );
    QString get_nom() {return nom ;}
    QString get_email () {return email ;}
    int get_cine () {return cine ;}
    QString get_chambre() {return id_chambre;}
    int get_cin(){return cine ;}
    void set_cine(int cine){ this->cine = cine;}
    void set_nom(QString nom ){ this->nom = nom ;}
    void set_email(QString email){this->email = email ;}
    void set_chambre (QString id_chambre) {this->id_chambre = id_chambre  ;}
   QSqlQueryModel*  afficher_foyer() ;
  QSqlQueryModel* afficher_demande() ;
};

#endif // FOYER_H
