#include "materiel.h"

Materiel::Materiel()
{

}

Materiel::~Materiel()
{

}

bool Materiel::ajouter()
{
    QSqlQuery q;
    q.prepare("INSERT INTO MATERIEL(IDMAT,QTEMAT,DATEMAT,NOMSTOCK,NOMMAT) "
              "VALUES(?,?,TO_DATE(?,'DD/MM/YYYY'),?,?)");
    q.addBindValue(IDMat);
    q.addBindValue(qteMat);
    q.addBindValue(DateMat);
    q.addBindValue(nomStock);
    q.addBindValue(nommat);
    return q.exec();
}

bool Materiel::modifier()
{
    QSqlQuery q;
    q.prepare("UPDATE MATERIEL"
              "SET IDMAT = ?, QTEMAT = ?, DATEMAT = ?, NOMSTOCK = ?, NOMMAT = ?"
              "WHERE IDMAT = ?");
    q.addBindValue(IDMat);
    q.addBindValue(qteMat);
    q.addBindValue(DateMat);
    q.addBindValue(nomStock);
    q.addBindValue(nommat);
    q.addBindValue(IDMat);
    return q.exec();
}

bool Materiel::suprimer()
{
    QSqlQuery q;
    q.prepare("DELETE FROM MATERIEL WHERE IDMAT = ?");
    q.addBindValue(IDMat);
    return q.exec();
}

void Materiel::ajouterArduino()
{
    QSqlQuery q;
    q.prepare("INSERT INTO MATERIEL(IDMAT,QTEMAT,DATEMAT,NOMSTOCK,NOMMAT,RFID_CODE) "
              "VALUES(?,?,TO_DATE(?,'DD/MM/YYYY'),?,?,?)");
    q.addBindValue(IDMat);
    q.addBindValue(qteMat);
    q.addBindValue(DateMat);
    q.addBindValue(nomStock);
    q.addBindValue(nommat);
    q.addBindValue(RFID_code);
    q.exec();
}
