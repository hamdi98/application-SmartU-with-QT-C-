#include "enseignant.h"
#include "ui_enseignant.h"
#include <QDebug>
#include<qmessagebox.h>
#include <QDialog>

enseignant::enseignant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::enseignant)
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

        notifyIcon =new QSystemTrayIcon(this);
        notifyIcon->setIcon(QIcon("C:/Users/user/Desktop/msg.png"));
}

enseignant::~enseignant()
{
    delete ui;
}

enseignant::enseignant (int CIN ,QString nom,QString prenom,QString matiere, int salaire )
{
  //this->id=id;
  this->CIN=CIN ;
  this->nom=nom;
  this->prenom=prenom;
  this->matiere =matiere;
    this->salaire=salaire ;


}

bool enseignant::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO PERSONNE(CIN,MAIL,MDP,NOM,PRENOM,DATEN,NATIONALITE) "
              "VALUES(?,?,?,?,?,TO_DATE(?,'DD/MM/YYYY'),?)");
query.addBindValue(CIN);
query.addBindValue(mail);
query.addBindValue(mdp);
query.addBindValue(nom);
query.addBindValue(prenom);
query.addBindValue(daten);
query.addBindValue(nationalite);
query.exec();
qDebug()<<"Executed the first insert query";
query.prepare("INSERT INTO enseignant ( CINN ,MATIERE,SALAIRE) "
                    "VALUES ( :CIN, :matiere, :salaire)");
query.bindValue(":CIN", CIN);
query.bindValue(":matiere", matiere);
query.bindValue(":salaire", salaire);
return    query.exec();
}
QSqlQueryModel * enseignant::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery *request = new QSqlQuery();
    request->prepare("select * from personne inner join enseignant on personne.cin=enseignant.cinn");
    request->exec();
    model->setQuery(*request);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Mail "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Nationalité"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Matiére"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Salaire"));
    return model;
}

bool  enseignant::supprimer()
{
      QSqlQuery *q = new QSqlQuery ();
      q->prepare("DELETE FROM enseignant WHERE CINN = ?");
      q->addBindValue(CIN);
      q->exec();
      q->prepare("DELETE FROM PERSONNE WHERE CIN= ?");
      q->addBindValue(CIN);
      q->exec();
      return q->exec();
}
bool enseignant :: modifier()
{
    QSqlQuery *q = new QSqlQuery ();
    q->prepare("UPDATE PERSONNE "
               "SET NOM = ? , PRENOM = ? , MAIL = ? , MDP = ? , DATEN = TO_DATE(?,'DD/MM/YYYY') , NATIONALITE = ?"
               "WHERE CIN = ?");
    q->addBindValue(nom);
    q->addBindValue(prenom);
    q->addBindValue(mail);
    q->addBindValue(mdp);
    q->addBindValue(daten);
    q->addBindValue(nationalite);
    q->addBindValue(CIN);
    q->exec();
    q->prepare("UPDATE ENSEIGNANT "
               "SET MATIERE = ? , SALAIRE = ? "
               "WHERE CINN = ?");
    q->addBindValue(matiere);
    q->addBindValue(salaire);
    q->addBindValue(CIN);
    return q->exec();

}


void enseignant::on_pb_ajouter_clicked()
{

      nom=ui->lineEdit_nom->text();
      prenom=ui->lineEdit_prenom->text();
      mail=ui->lineEdit_Mail->text();
      mdp=ui->lineEdit_MDP->text();
      CIN=ui->lineEdit_CIN->text().toInt();
      daten=ui->lineEdit_Date->text();
      nationalite=ui->lineEdit_nationalite->text();
      salaire=ui->lineEdit_Salaire->text().toInt();
      matiere=ui->lineEdit_Matiere->text();
      bool test=ajouter();
      if(test)
    {ui->tableView->setModel(afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Ajouter un enseignant"),
                      QObject::tr("Enseignant ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    notifyIcon->show();
    notifyIcon->showMessage("info","ajouté",QSystemTrayIcon::Information,2);




    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un enseignant"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);



}

void enseignant::on_pushButton_2_clicked()
{
    ui->tableView->setModel(afficher());
}

void enseignant::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "suppression d'enseignant", "Voulez-vous vraiement supprimer cet enseignant ?",
                                       QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::Yes) {
             CIN = ui->tableView->model()->index(ui->tableView->currentIndex().row(),0).data().toInt();

             bool test = supprimer();
             if (test)
             {
              QMessageBox::information(nullptr, QObject::tr("Supprimer enseignant"),
                          QObject::tr( "Supprimer avec sucess ,Click Cancel to exit."), QMessageBox::Cancel);
             }
             else
              QMessageBox::warning(nullptr, QObject::tr("Supprimer enseignant !"),
                          QObject::tr( "Erreur,Click Cancel to exit."), QMessageBox::Cancel);
              on_pushButton_2_clicked();
         }}



bool enseignant::on_lineEdit_CIN_editingFinished()
{
    if (ui->lineEdit_CIN->text().toLong() == 0)
    {
        ui->label_3->setText("Remarque :\n"
                             " le numéro de carte d'identité ne contient que des chiffres");
        ui->label_3->setStyleSheet("QLabel {color : red; }");

        return false;
    }else {ui->label_3->setText("✓");
         ui->label_3->setStyleSheet("QLabel {color : green; }");
         return true;}
}


void enseignant::on_lineEdit_3_textChanged(const QString &arg1)
{

    QSqlQuery *q = new QSqlQuery ();
    QSqlQueryModel *model = new QSqlQueryModel();
   // ui->text->setText(arg1);

    q->prepare("SELECT * FROM enseignantt WHERE  "+ui->comboBox->currentText()+" LIKE '"+arg1+"%'");
    q->exec();
    model->setQuery(*q);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Matiere"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
    ui->tableView->setModel(model);
   // ui->tableView->setColumnHidden(0,true);
}



void enseignant::on_tableView_doubleClicked()
{
    ui->lineEdit_CIN->setText(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0).data().toString());
    ui->lineEdit_Mail->setText(ui->tableView->model()->index(ui->tableView->currentIndex().row(),1).data().toString());
    ui->lineEdit_MDP->setText(ui->tableView->model()->index(ui->tableView->currentIndex().row(),2).data().toString());
    ui->lineEdit_nom->setText(ui->tableView->model()->index(ui->tableView->currentIndex().row(),3).data().toString());
    ui->lineEdit_prenom->setText(ui->tableView->model()->index(ui->tableView->currentIndex().row(),4).data().toString());
    ui->lineEdit_Date->setText(ui->tableView->model()->index(ui->tableView->currentIndex().row(),5).data().toString());
    ui->lineEdit_nationalite->setText(ui->tableView->model()->index(ui->tableView->currentIndex().row(),6).data().toString());
    ui->lineEdit_Matiere->setText(ui->tableView->model()->index(ui->tableView->currentIndex().row(),8).data().toString());
    ui->lineEdit_Salaire->setText(ui->tableView->model()->index(ui->tableView->currentIndex().row(),9).data().toString());
}

void enseignant::on_pb_modifier_clicked()
{
    CIN = ui->tableView->model()->index(ui->tableView->currentIndex().row(),0).data().toInt();
    nom=ui->lineEdit_nom->text();
    prenom=ui->lineEdit_prenom->text();
    mail=ui->lineEdit_Mail->text();
    mdp=ui->lineEdit_MDP->text();
    daten=ui->lineEdit_Date->text();
    nationalite=ui->lineEdit_nationalite->text();
    salaire=ui->lineEdit_Salaire->text().toInt();
    matiere=ui->lineEdit_Matiere->text();
      modifier();
      on_pushButton_2_clicked();
}

void enseignant :: send ()
{
     QString l;
     QSqlQuery q;
    QByteArray d;
   l=ui->label_Arduino->text();
   q.prepare("select * from enseignant  where CINN=:l1");
   q.bindValue(":l1",l);
  if (q.exec())
  {
      int count=0;
      while(q.next())
      {
          count++;
      }
      if (count==1)
      {
          d="1";
          A.write_to_arduino(d);
      }
      else
      {
          d="2";
          A.write_to_arduino(d);
      }
  }


}

void enseignant::update_label()
{
  QByteArray data=A.read_from_arduino();
  ui->label_Arduino->setText(data);
  send();


    //sendard();
}
/*void enseignant::sendard()
{
    //A.write_to_arduino("1");
}*/
