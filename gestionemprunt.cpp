#include "gestionemprunt.h"
#include "ui_gestionemprunt.h"

GestionEmprunt::GestionEmprunt(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GestionEmprunt)
{
    ui->setupUi(this);
}

GestionEmprunt::~GestionEmprunt()
{
    delete ui;
}

void GestionEmprunt::refreshtableemprunt()
{
    QSqlQuery *q = new QSqlQuery();
    QSqlQueryModel *m = new QSqlQueryModel();
    q->prepare("SELECT * FROM EMPRUNT");
    q->exec();
    m->setQuery(*q);
    m->setHeaderData(1, Qt::Horizontal, tr("Nom du livre"));
    m->setHeaderData(2, Qt::Horizontal, tr("Categorie"));
    m->setHeaderData(3, Qt::Horizontal, tr("Date d'emprunt"));
    m->setHeaderData(4, Qt::Horizontal, tr("CIN"));
    ui->tableView_2->setModel(m);
    ui->tableView_2->setColumnHidden(0,true);
    ui->tableView_2->setColumnWidth(1,ui->tableView_2->width()/4);
    ui->tableView_2->setColumnWidth(2,ui->tableView_2->width()/4);
    ui->tableView_2->setColumnWidth(3,ui->tableView_2->width()/4);
    ui->tableView_2->setColumnWidth(4,ui->tableView_2->width()/4);
}

void GestionEmprunt::on_AjouterClasse_released()
{
    if((ui->nomlivre->text().size()>0)&&(ui->categorie->text().size()>0)&&(ui->cin->text().size()>0)&&(ui->date->text().size()>0))
    {
        Emprunt *e = new Emprunt();
        e->Setcat(ui->categorie->text());
        e->Setcin(ui->cin->text());
        e->Setdate(ui->date->text());
        e->Setid("1");
        e->Setlivre(ui->nomlivre->text());
        e->creer();
        delete e;
        refreshtableemprunt();
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Détails insuffisants",QMessageBox::Ok);
    }
}

void GestionEmprunt::on_ModifierClasse_released()
{
    if((ui->nomlivre->text().size()>0)&&(ui->categorie->text().size()>0)&&(ui->cin->text().size()>0)&&(ui->date->text().size()>0)&&(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toString().size()>0))
    {
        Emprunt *e = new Emprunt();
        e->Setid(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toString());
        e->Setcat(ui->categorie->text());
        e->Setcin(ui->cin->text());
        e->Setdate(ui->date->text());
        e->Setlivre(ui->nomlivre->text());
        e->modifier();
        delete e;
        refreshtableemprunt();
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Veuillez selectionner un emprunt du tableau à modifier et complétez les détails",QMessageBox::Ok);
    }
}


void GestionEmprunt::on_AfficherClasse_released()
{
    refreshtableemprunt();
}

void GestionEmprunt::on_SuppClasse_released()
{
    if(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toString().size()>0)
    {
        Emprunt *e = new Emprunt();
        e->Setid(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toString());
        e->supprimer();
        refreshtableemprunt();
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Veuillez selectionner un abonnement du tableau à supprimer",QMessageBox::Ok);
    }
}

void GestionEmprunt::on_tableView_2_clicked(const QModelIndex &index)
{
    ui->nomlivre->setText(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),1).data().toString());
    ui->categorie->setText(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),2).data().toString());
    ui->date->setText(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),3).data().toString());
    ui->cin->setText(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),4).data().toString());
}

void GestionEmprunt::on_lineEdit_2_textChanged(const QString &arg1)
{
    QSqlQuery *q = new QSqlQuery();
    QSqlQueryModel *m = new QSqlQueryModel();
    switch(ui->comboBox->currentIndex())
    {
        case 0 :
        {
            q->prepare("SELECT * FROM EMPRUNT WHERE NOMLIVRE = ?");
        }
        break;
        case 1 :
        {
            q->prepare("SELECT * FROM EMPRUNT WHERE CATEGORIE = ?");
        }
        break;
        case 2 :
        {
            q->prepare("SELECT * FROM EMPRUNT WHERE CIN = ?");
        }
        break;
    }
    q->addBindValue(arg1);
    q->exec();
    m->setQuery(*q);
    m->setHeaderData(1, Qt::Horizontal, tr("Nom du livre"));
    m->setHeaderData(2, Qt::Horizontal, tr("Categorie"));
    m->setHeaderData(3, Qt::Horizontal, tr("Date d'emprunt"));
    m->setHeaderData(4, Qt::Horizontal, tr("CIN"));
    ui->tableView_2->setModel(m);
    ui->tableView_2->setColumnHidden(0,true);
    ui->tableView_2->setColumnWidth(1,ui->tableView_2->width()/4);
    ui->tableView_2->setColumnWidth(2,ui->tableView_2->width()/4);
    ui->tableView_2->setColumnWidth(3,ui->tableView_2->width()/4);
    ui->tableView_2->setColumnWidth(4,ui->tableView_2->width()/4);
}
