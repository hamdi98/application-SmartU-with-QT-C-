#include "foyerui.h"
#include "ui_foyerui.h"
#include"foyer.h"
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include"qmessagebox.h"
#include<QVariant>
#include <QModelIndex>
#include <iostream>
#include<QString>
#include"smtp.h"



foyerui::foyerui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::foyerui)
{
    ui->setupUi(this);
     ui->table->setModel( tmpetudiant.afficher_foyer());
      ui->table2->setModel( tmpetudiant.afficher_demande());
}

foyerui::~foyerui()
{
    delete ui;
}



void foyerui::on_ajouter_clicked()
{

    int   cine1 = ui->cin ->text().toInt() ;
     QString  nom1 = ui ->nom->text() ;
     QString email1 = ui->email->text() ;
     QString id_chambre1 = ui->ch ->text() ;

     Foyer e(cine1 ,nom1 ,email1 ,id_chambre1) ;
     bool test = e.ajouter() ;
        tmpetudiant.afficher_foyer();




     if (test)
     {

         Smtp* smtp = new Smtp("mariemchtourou988@gmail.com", "238118155", "smtp.gmail.com", 465);
             connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
                 smtp->sendMail("ESPRIT", email1 , "SmartU, You've been added!","Congrats! You've been added to PEOPLE in SmartU!");



         QMessageBox::information(nullptr, QObject::tr("ajouter avec sucess !"),
                     QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);
    }

     else
         QMessageBox::critical(nullptr, QObject::tr("ajouter non sucess !"),
                     QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);

}




void foyerui::on_rechercher_textChanged(const QString &arg1)
{
    QSqlQuery *q =new QSqlQuery() ;
        QSqlQueryModel * model = new QSqlQueryModel() ;
       q->prepare("select * from foyer where  CINE = :arg1");
       q->bindValue(":arg1",arg1);
       q->exec();
       model->setQuery(*q);
       ui->table->setModel(model);

}

void foyerui::on_table_doubleClicked(const QModelIndex &index)
{
    QString selectcin = ui->table->model()->data(index).toString() ;
    QSqlQuery q ;
    q.prepare( "select cine , nom , email ,id_chambre  from foyer where cine ="+ selectcin +"");
    if (q.exec())
    {

           while (q.next())
           {
               ui->cin->setText(q.value(0).toString()) ;
               ui->nom->setText(q.value(1).toString()) ;
               ui->email->setText(q.value(2).toString()) ;
               ui->ch->setText(q.value(3).toString()) ;

           }



}
}

void foyerui::on_modifier_clicked()
{
    Foyer e ;

    int id =ui->cin->text().toInt() ;
    QString  nom1 =ui->nom->text() ;
    QString email1 = ui->email->text() ;
    QString id_chambre1 = ui->ch->text();





    bool test = e.modifier(id,nom1,email1,id_chambre1);
    if (test)
    {
         ui->table->setModel( tmpetudiant.afficher_foyer());

        QMessageBox::information(nullptr, QObject::tr("modifier avec sucess !"),
                    QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("modifier non sucess !"),
                    QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);





}

void foyerui::on_supprimer1_clicked()
{

    QModelIndex index ;
           index  = ui->table->selectionModel()->currentIndex();
    int  value;
    value = index.sibling(index.row(),index.column()).data().toInt() ;
            Foyer e ;
    bool test = e.supp2(value);
    QSqlQueryModel * model = new QSqlQueryModel() ;

    model = e.afficher_foyer() ;
    ui->table->setModel(model);
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Supprimer avec sucess !"),
                    QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer non sucess !"),
                    QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);


}

void foyerui::on_supprimer1_2_clicked()
{

    QModelIndex index ;
           index  = ui->table2->selectionModel()->currentIndex();
    int  value;
    value = index.sibling(index.row(),index.column()).data().toInt() ;
            Foyer e ;
    bool test = e.supp(value);
    QSqlQueryModel * model = new QSqlQueryModel() ;

    model = e.afficher_demande() ;
    ui->table2->setModel(model);
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Supprimer avec sucess !"),
                    QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer non sucess !"),
                    QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);


}

void foyerui::on_afficher_2_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery *request=new QSqlQuery();

        request->prepare("SELECT *FROM demandef");
        request->exec();
        model->setQuery(*request);

        ui->table2->setModel(model);

}

void foyerui::on_afficher_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery *request=new QSqlQuery();

        request->prepare("SELECT *FROM foyer");
        request->exec();
        model->setQuery(*request);

        ui->table->setModel(model);

}
