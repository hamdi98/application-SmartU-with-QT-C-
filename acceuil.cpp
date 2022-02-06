#include "acceuil.h"
#include "ui_acceuil.h"

acceuil::acceuil(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::acceuil)
{
    ui->setupUi(this);
}

acceuil::~acceuil()
{
    delete ui;
}

void acceuil::remplir(QString login, int type)
{
    QSqlQuery q,qbonus;
    q.prepare("SELECT * FROM PERSONNE WHERE MAIL=?");
    q.addBindValue(login);
    q.exec();
    q.first();
    ui->cinlabel->setText(q.value(0).toString());
    ui->nomlabel->setText(q.value(3).toString());
    ui->prenomlabel->setText(q.value(4).toString());
    ui->datelabel->setText(q.value(5).toString());
    ui->nationalitelabel->setText(q.value(6).toString());
    switch(type)
    {
    case 1 :
    {
        ui->Bonus->setHidden(true);
        ui->Bonus_2->setHidden(true);
        ui->Bonus_3->setHidden(true);
        ui->Bonus_4->setHidden(true);
        ui->Bonuslabel->setHidden(true);
        ui->Bonuslabel_2->setHidden(true);
        ui->Bonuslabel_3->setHidden(true);
        ui->Bonuslabel_4->setHidden(true);
    }
        break;
    case 2 :
    {
        ui->Bonus->setText("Departement :");
        qbonus.prepare("SELECT * FROM STAFF WHERE CINS=?");
        qbonus.addBindValue(q.value(0));
        qbonus.exec();
        qbonus.first();
        ui->Bonuslabel->setText(qbonus.value(1).toString());
        ui->Bonus_2->setHidden(true);
        ui->Bonus_3->setHidden(true);
        ui->Bonus_4->setHidden(true);
        ui->Bonuslabel_2->setHidden(true);
        ui->Bonuslabel_3->setHidden(true);
        ui->Bonuslabel_4->setHidden(true);
    }
        break;
    case 3 :
    {
        ui->Bonus->setText("Matiére :");
        qbonus.prepare("SELECT * FROM ENSEIGNANT WHERE CINN=?");
        qbonus.addBindValue(q.value(0));
        qbonus.exec();
        qbonus.first();
        ui->Bonuslabel->setText(qbonus.value(1).toString());
        ui->Bonus_2->setHidden(true);
        ui->Bonus_3->setHidden(true);
        ui->Bonus_4->setHidden(true);
        ui->Bonuslabel_2->setHidden(true);
        ui->Bonuslabel_3->setHidden(true);
        ui->Bonuslabel_4->setHidden(true);
    }
        break;
    case 4 :
    {
        ui->Bonus->setText("Solde :");
        ui->Bonus_2->setText("Club :");
        ui->Bonus_3->setText("Credits :");
        ui->Bonus_4->setText("Classe :");
        qbonus.prepare("SELECT * FROM ETUDIANT WHERE CINE=?");
        qbonus.addBindValue(q.value(0));
        qbonus.exec();
        qbonus.first();
        ui->Bonuslabel->setText(qbonus.value(1).toString());
        ui->Bonuslabel_2->setText(qbonus.value(2).toString());
        ui->Bonuslabel_3->setText(qbonus.value(3).toString());
        ui->Bonuslabel_4->setText(qbonus.value(4).toString());
    }
        break;
    }
}

QString acceuil::getnom()
{
    return ui->nomlabel->text();
}
