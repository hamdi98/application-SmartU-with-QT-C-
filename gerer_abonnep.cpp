#include "gerer_abonnep.h"
#include "ui_gerer_abonnep.h"
#include "abonnep.h"
#include<QSqlQuery>
#include<QSqlError>
#include<iostream>
#include<QSqlQueryModel>
#include<QMessageBox>
#include "place.h"
#include"demande_parking.h"

gerer_abonneP::gerer_abonneP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gerer_abonneP)
{
    ui->setupUi(this);

    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).


    notify =new QSystemTrayIcon(this);
    notify->setIcon(QIcon("icon.png"));
    notify->setVisible(true);
    ui->tabP->setSelectionBehavior(QAbstractItemView::SelectRows);//TABLEAU PARKING
ui->tabplace->setSelectionBehavior(QAbstractItemView::SelectRows);//TABLEAU PLACE PARKING
ui->TABDE->setSelectionBehavior(QAbstractItemView::SelectRows);//TABLEAU DEMANDE ABONNEMENT

    ui->filtre_abo->addItem("Nom");
    ui->filtre_abo->addItem("Prenom");
}



gerer_abonneP::~gerer_abonneP()
{
    delete ui;
}

void gerer_abonneP::on_save_clicked()
{

    notify->show();
    notify->showMessage(tr("info"),tr("vous etes abonne"),QSystemTrayIcon::Information,10000);
    QString nom= ui->nom->text();
    QString prenom= ui->prenom->text();


    abonneP e(nom,prenom);

    QSqlQuery Q;
      bool test=e.ajouter();
      if(test)
      {

        ui->tabP->setModel(e.afficher());
        ui->tabP->setColumnHidden(0,true);

        QMessageBox::information(nullptr, QObject::tr("Ajouter un abonne au parking"),
                                 QObject::tr("abonne ajouté.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

      }
      else
      {
      //    QMessageBox::critical(this,tr("Ajouter un abonne au parking"),query.lastError().text());
      }

}

void gerer_abonneP::on_supprimer_clicked()
{
    QModelIndex index=ui->tabP->currentIndex().sibling(ui->tabP->currentIndex().row(),0);//2

    abonneP e;
    if(e.supprimer(index.data().toString()))
    ui->tabP->setModel(e.afficher());
}

//void gerer_abonneP::on_afficher_clicked()
//{
   // abonneP abo;

   // ui->tabP->setModel(abo.afficher());
    //ui->tabP->setColumnHidden(2,true);
//};

void gerer_abonneP::on_lineEdit_textChanged(const QString &arg1)
{
    abonneP abo;
    ui->tabP->setModel(abo.afficher());
    ui->tabP->setColumnHidden(0,true);
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel();

    proxy->setSourceModel(ui->tabP->model());
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterKeyColumn(ui->filtre_abo->currentIndex()+1);
    proxy->setFilterFixedString(arg1);

    ui->tabP->setModel(proxy);
}



void gerer_abonneP::on_modifier_clicked()
{
    abonneP abo(ui->nom->text(),ui->prenom->text());
    if(abo.modifier(ui->tabP->model()->data(ui->tabP->currentIndex().sibling(ui->tabP->currentIndex().row(),0)).toString()))
    {
        ui->tabP->setModel(abo.afficher());
        ui->tabP->setColumnHidden(0,true);
        ui->nom->setText("");
        ui->prenom->setText("");
    }
}

void gerer_abonneP::on_tabP_activated(const QModelIndex &index)
{
    QModelIndex header=index.sibling(index.row(),0);
    QString val=ui->tabP->model()->data(header).toString();
    abonneP abo;

    QSqlQuery query=abo.afficherAbo(val);
    if(query.exec())
    {
        while(query.next())
        {
            ui->prenom->setText(query.value(2).toString());//1
            ui->nom->setText(query.value(1).toString());//0

        }

    }

}



void gerer_abonneP::on_retourner_clicked()
{
    //choisir C;
        //close();
        //C.exec();
        //C.show();
}

void gerer_abonneP::on_ajouterplaceparking_clicked()
{
    QSqlQuery query;
   abonneP abo;
   QString ID= ui->id5->text();
   QString num= ui->num5->text();

     if (abo.rechercheID(ID))
     {
         place f(num,ID);
       bool test=f.ajouter();
           if(test)
           {
               QMessageBox::information(nullptr, QObject::tr("ajouter "),
                                 QObject::tr("ajouter.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

          }
             else
             {  QMessageBox::information(this,tr("IMPOSSIBLE"),query.lastError().text());


             }
     }
}

void gerer_abonneP::on_afficherplaceparking_clicked()
{
    QSqlQueryModel *m= new QSqlQueryModel();
   QSqlQuery *request=new QSqlQuery();

   request->prepare("select   *from  PLACEP ");
   request->exec();

   m->setQuery(*request);
   ui->tabplace->setModel(m);
}

void gerer_abonneP::on_modifierplaceparking_clicked()
{
}

void gerer_abonneP::on_supprimerplaceparking_clicked()
{
    QModelIndex index=ui->tabplace->currentIndex().sibling(ui->tabplace->currentIndex().row(),0);//2

    place p;
    if(p.supprimer(index.data().toString()))
    ui->tabplace->setModel(p.afficher());
}

//void gerer_abonneP::on_tabplace_activated(const QModelIndex &index)
//{

//}

void gerer_abonneP::on_GESTIONABONNEPARKING_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void gerer_abonneP::on_GESTIONPLACEPARKING_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}

void gerer_abonneP::on_afficher_demande_clicked()
{
    QSqlQueryModel *m= new QSqlQueryModel();
   QSqlQuery *request=new QSqlQuery();

   request->prepare("select   *from  DEMANDEP ");
   request->exec();

   m->setQuery(*request);
   ui->TABDE->setModel(m);
}


void gerer_abonneP::on_consulterdemande_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void gerer_abonneP::on_demandeabonnement_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void gerer_abonneP::on_envoyerdemandeabonnement_clicked()
{
    notify->show();
    notify->showMessage(tr("info"),tr("Demande envoye"),QSystemTrayIcon::Information,10000);


    QString nom= ui->NOM->text();
    QString prenom= ui->PRENOM->text();
    QString CIN= ui->CIN->text();
    QString date= ui->DATE ->text();
    QString EMAIL= ui->EMAIL->text();

    demande_parking d(nom,prenom,CIN,EMAIL,date);
    QSqlQuery Q;
      bool test=d.ajouter();
      if(test)
      {



        QMessageBox::information(nullptr, QObject::tr("demande envoyer"),
                                 QObject::tr("demnade envoye.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

      }

}

void gerer_abonneP::on_supprimer_demande_clicked()
{
    QModelIndex index=ui->TABDE->currentIndex().sibling(ui->TABDE->currentIndex().row(),0);//2

demande_parking d;
    if(d.supprimer(index.data().toString()))
    ui->TABDE->setModel(d.afficher());
}

//void gerer_abonneP::on_TABDE_activated(const QModelIndex &index)
//{

//}

void gerer_abonneP::on_val_clicked()
{


}
void gerer_abonneP::update_label()
{
    data=A.read_from_arduino();
    ui->frr->setText(data);
   sendard();


}
void gerer_abonneP:: sendard ()
{
     A.write_to_arduino("1");
        }
