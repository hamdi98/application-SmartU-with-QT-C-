#include "niveauclasse.h"
#include "ui_niveauclasse.h"
#include <QMessageBox>
#include <QDebug>
niveauclasse::niveauclasse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::niveauclasse)
{
    ui->setupUi(this);
}

niveauclasse::~niveauclasse()
{
    delete ui;
}


niveauclasse::niveauclasse( QString nom ,QString annee ,QString branche , int NbrEtudiant)
{   this->nom=nom ;
    this->annee=annee ;
    this->branche=branche ;
    this->NbrEtudiant=NbrEtudiant ;
}
QString niveauclasse::get_annee(){return  annee;}
QString niveauclasse::get_branche(){return branche;}
int niveauclasse::get_NbrEtudiant(){return  NbrEtudiant;}
QString niveauclasse ::get_nom (){return nom ;}

bool niveauclasse::ajouter()
{
QSqlQuery query;
QString res2= QString::number(NbrEtudiant);


query.prepare("INSERT INTO CLasse (ID,ANNEE,NOM,BRANCHE,NBRETUDIANT) VALUES (CLASSE_SEQ.nextval,?,?,?,?)");
query.addBindValue(annee);
query.addBindValue(branche);
query.addBindValue(nom);
query.addBindValue(res2);
return    query.exec();
}
QSqlQueryModel * niveauclasse::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
     QSqlQuery *request = new QSqlQuery();
    request->prepare("select * from CLasse");
    request->exec();
    model->setQuery(*request);
model->setQuery("select * from CLasse");

model->setHeaderData(1, Qt::Horizontal, QObject::tr("Annee"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Branche "));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("NbrEtudiant"));
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));



return model;
}
bool  niveauclasse::supprimer(int i)
{
      QSqlQuery *q = new QSqlQuery ();
      q->prepare("DELETE FROM CLasse WHERE ID  = ?");
      q->addBindValue(i);
      return q->exec();
}

void niveauclasse::on_AfficherClasse_clicked()
{
    niveauclasse tmp ;

       ui->tableView_2->setModel(tmp.afficher());

        ui->tableView_2->setColumnHidden(0,true);


}

void niveauclasse::on_AjouterClasse_clicked()
{
    QString Annee= ui->lineEdit_4->text();
    QString Branche= ui->lineEdit_6->text();
    int NbrEtudiant = ui->lineEdit_7->text().toInt();
    QString Nom=ui->lineEdit->text();

  niveauclasse n(Nom,Annee,Branche,NbrEtudiant);
  bool test=n.ajouter();
  if(test)
{ui->tableView_2->setModel(n.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter une classe"),
                  QObject::tr("classe ajoutée.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une classe"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void niveauclasse::on_SuppClasse_clicked()
{
    QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "suppression du classe", "Voulez-vous vraiment supprimer cette classe?",
                                       QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::Yes) {

                int i = ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toInt();

                  niveauclasse n ;
             bool test = n.supprimer(i);
             if (test)
             {
              QMessageBox::information(nullptr, QObject::tr("Supprimer classe"),
                          QObject::tr( "Supprimer avec sucess ,Click Cancel to exit."), QMessageBox::Cancel);
             }
             else
              QMessageBox::warning(nullptr, QObject::tr("Supprimer classe !"),
                          QObject::tr( "Erreur,Click Cancel to exit."), QMessageBox::Cancel);
             on_AfficherClasse_clicked();
         }

}
bool niveauclasse :: modifier( QString nom, QString annee ,  QString branche , int NbrEtudiant, int id )
{

    QString res1= QString:: number (NbrEtudiant) ;
    QSqlQuery *q = new QSqlQuery ();
    q->prepare("UPDATE CLasse set NOM=:nom ,ANNEE=:annee, BRANCHE=:branche , NBRETUDIANT=:NbrEtudiant WHERE ID= :id");
    q->bindValue(":nom",nom);
    q->bindValue(":annee",annee);
    q->bindValue(":branche" ,branche);
    q->bindValue(":NbrEtudiant",res1);
    q->bindValue(":id",id);
    return q->exec();

}

void niveauclasse::on_ModifierClasse_clicked()
{
        int i = ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toInt();
        niveauclasse n ;
        QString Nom = ui->lineEdit->text ();
        QString Annee =ui->lineEdit_4->text() ;
        QString Branche = ui->lineEdit_6->text() ;
        int Nbr =ui->lineEdit_7->text().toInt();
        n.modifier(Nom,Annee,Branche,Nbr,i);

on_AfficherClasse_clicked();
}

void niveauclasse::on_pushButton_4_clicked()
{
    hide () ;
    niveauclasse l ;
    l.show ();
}
void niveauclasse::on_lineEdit_2_textChanged(const QString &arg1)
{

    QSqlQuery *q = new QSqlQuery ();
    QSqlQueryModel *model = new QSqlQueryModel();
   // ui->text->setText(arg1);

    q->prepare("SELECT * FROM CLASSE WHERE  "+ui->comboBox->currentText()+" LIKE '"+arg1+"%'");
    q->exec();
    model->setQuery(*q);
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Annee"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Branche "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NbrEtudiant"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    ui->tableView_2->setModel(model);
   // ui->tableView_2>setColumnHidden(0,true);
}


void niveauclasse::on_tableView_2_doubleClicked()
{
    QString val = ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toString();
      QSqlQuery q;
      q.prepare("select * from CLASSE where ANNEE='"+val+"'or NOM='"+val+"'or BRANCHE='"+val+"'");

      ui->lineEdit_4->setText(q.value(1).toString());
      ui->lineEdit->setText(q.value(2).toString());
      ui->lineEdit_6->setText(q.value(3).toString());
     // ui->lineEdit_7->setText(q->value(4).toString());


}
