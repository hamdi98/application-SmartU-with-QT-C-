#include "staff.h"

Staff::Staff():Personne ()
{

}

Staff::~Staff()
{

}


void Staff::repondre(int id, bool rep,QString daterep)
{
    QSqlQuery q,q1,q2,q3;
    QString temp;
    int temp2;
    if(rep)
    {
        q.prepare("SELECT * FROM DEMANDE WHERE IDDEMANDE = ?");
        q.addBindValue(id);
        q.exec();
        Recu *r = new Recu();
        if(q.first())
        {
            qDebug() << "Found demand";
            r->setid(q.value(0).toString());
            r->setqte(q.value(1).toInt());
            r->setidmat(q.value(2).toString());
            r->setcin(q.value(3).toInt());
            r->setdate(daterep); //Get the current date
            q1.prepare("SELECT * FROM MATERIEL WHERE IDMAT = ?");
            q1.addBindValue(q.value(2).toString());
            q1.exec();
            qDebug() << q1.first();
            temp2=q1.value(1).toInt();
            qDebug() << temp2;
            if(temp2>=r->getqte())
            {
                if(r->creerrecu())
                {
                    q3.prepare("DELETE FROM DEMANDE WHERE IDDEMANDE = ?");
                    q3.addBindValue(r->getid());
                    q3.exec();
                    q2.prepare("UPDATE MATERIEL SET QTEMAT = QTEMAT - ? WHERE IDMAT = ?");
                    q2.addBindValue(q.value(1).toInt());
                    q2.addBindValue(q.value(2).toString());
                    if(q2.exec())
                    {
                        qDebug() << "Decremented";
                    }
                }
                else
                {
                    qDebug() << "Values not added";
                }
            }
            else
            {
                qDebug() << "Values not added, not enough quantity";
            }
        }
        else
        {
            qDebug() << "Error, demand not found";
        }
        delete r;
    }
    else
    {
        q.prepare("DELETE FROM DEMANDE WHERE IDDEMANDE = ?");
        q.addBindValue(id);
        q.exec();
    }
}
