#ifndef RECU_H
#define RECU_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


class Recu
{
public:
    Recu();
    ~Recu();
    bool creerrecu();
    void setid(QString id){IDRecu=id;}
    void setqte(int qte){qteRecu=qte;}
    void setidmat(QString id2){IDMat=id2;}
    void setcin(int cin){CINN=cin;}
    QString getid(){return IDRecu;}
    int getqte(){return qteRecu;}
    void setdate(QString d){date=d;}
private:
    QString IDRecu;
    int qteRecu;
    QString IDMat;
    int CINN;
    QString date;
};

#endif // RECU_H
