#ifndef DEMANDE_H
#define DEMANDE_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class Demande
{
public:
    Demande();
    ~Demande();
    bool creerdemande();
    void setid(QString id){IDDemande=id;}
    void setqte(int qte){qteDemande=qte;}
    void setidmat(QString id2){IDMat=id2;}
    void setcin(int cin){CINN=cin;}
    void setdate(QString d){date=d;}
    void afficher();
    void annuler();
private:
    QString IDDemande;
    int qteDemande;
    QString IDMat;
    int CINN;
    QString date;
};

#endif // DEMANDE_H
