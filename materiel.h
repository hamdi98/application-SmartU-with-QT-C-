#ifndef MATERIEL_H
#define MATERIEL_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class Materiel
{
public:
    Materiel();
    ~Materiel();
    bool ajouter();
    bool modifier();
    bool suprimer();
    void setid(QString id){IDMat=id;}
    void setqte(int qte){qteMat=qte;}
    void setdate(QString date){DateMat=date;}
    void setnom(QString noms){nomStock=noms;}
    void setnommat(QString nom){nommat=nom;}
    void setrfid(QString code){RFID_code=code;}
    void ajouterArduino();
private:
    QString IDMat;
    int qteMat;
    QString DateMat;
    QString nomStock;
    QString nommat;
    QString RFID_code;
};

#endif // MATERIEL_H
