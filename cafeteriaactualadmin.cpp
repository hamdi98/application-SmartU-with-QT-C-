#include "cafeteriaactualadmin.h"
#include "ui_cafeteriaactualadmin.h"

cafeteriaactualadmin::cafeteriaactualadmin(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::cafeteriaactualadmin)
{
    ui->setupUi(this);
    Produit p;
    QSqlQueryModel* model=new QSqlQueryModel();
    model=p.afficherBuvette();
    ui->Affichage_produit->setModel(model);
    int ret=A.connect_arduino();
    switch(ret)
    {
         case(0):qDebug()<<"arduino is available and connected to : "<<A.getarduino_port_name();
             break;
         case(1):qDebug()<<"arduino is available but not connected to : "<<A.getarduino_port_name();
             break;
         case(-1):qDebug()<<"arduino is not available";
             break;
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

cafeteriaactualadmin::~cafeteriaactualadmin()
{
    delete ui;
}

void cafeteriaactualadmin::on_pushButton_9_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery q;
    QString id=ui->research->text();
    q.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT from PRODUIT where IDPRODUIT like ? ");
    q.addBindValue("%"+id+"%");
    if (q.exec())
    {
        model->setQuery(q);
        ui->Affichage_produit->setModel(model);
    }
}

void cafeteriaactualadmin::on_pushButton_8_clicked()
{
    QSqlQuery qry1;
    Produit p;
    QSqlQueryModel *model=new QSqlQueryModel();
    int currentcol=ui->comboBox_4->currentIndex();

    if (currentcol==0)
    {qry1.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT from PRODUIT ");}

    else if (currentcol==1)
    {qry1.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT from PRODUIT where IDBUVETTE=(?)");
        qry1.addBindValue(23);}

    else if (currentcol==2)
    {qry1.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT from PRODUIT where IDBUVETTE=(?)");
        qry1.addBindValue(24);}

    else if (currentcol==3)
    {qry1.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT from PRODUIT where IDBUVETTE=(?)");
        qry1.addBindValue(25);}

    else if (currentcol==4)
    {qry1.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT from PRODUIT where IDBUVETTE=(?)");
        qry1.addBindValue(26);}

    if (qry1.exec())
    {
        model->setQuery(qry1);
        ui->Affichage_produit->setModel(model);
    }
}

void cafeteriaactualadmin::on_pushButton_people_5_clicked()
{
    Produit p;
    p.set_IDProduit(ui->idproduit->text());
    p.supprimerProduit();
    QSqlQueryModel* model=new QSqlQueryModel();
    model=p.afficherBuvette();
    ui->Affichage_produit->setModel(model);
}

void cafeteriaactualadmin::on_Affichage_produit_doubleClicked(const QModelIndex &index)
{
    QString selectedIDPRODUIT=ui->Affichage_produit->model()->data(index).toString();
    QSqlQuery qry2;
    qry2.prepare("select IDPRODUIT,QTEPRODUIT,DATEPRODUIT,PRIXPRODUIT,IDBUVETTE from PRODUIT where IDPRODUIT=(?) ");
    qry2.addBindValue(selectedIDPRODUIT);
       if (qry2.exec())
       {
           while (qry2.next())
           {
               ui->idproduit->setText(qry2.value(0).toString());
               ui->qteproduit->setText(qry2.value(1).toString());
               ui->dateproduit->setText(qry2.value(2).toString());
               ui->prixproduit->setText(qry2.value(3).toString());
               if (qry2.value(4).toString()=="23")
                       ui->comboBox_idbuvette->setCurrentIndex(1);
               else if (qry2.value(4).toString()=="24")
                   ui->comboBox_idbuvette->setCurrentIndex(2);
               else if (qry2.value(4).toString()=="25")
                   ui->comboBox_idbuvette->setCurrentIndex(3);
               else if (qry2.value(4).toString()=="26")
                   ui->comboBox_idbuvette->setCurrentIndex(4);
           }
       }
}

void cafeteriaactualadmin::on_pushButton_6_clicked()
{
    Produit p;
    p.set_qteProduit(ui->qteproduit->text().toInt());
    p.set_PrixProduit(ui->prixproduit->text());
    p.set_DateProduit(ui->dateproduit->text());
    p.set_IDProduit(ui->idproduit->text());
    p.modifierProduit();
    QSqlQueryModel* model=new QSqlQueryModel();
    model=p.afficherBuvette();
    ui->Affichage_produit->setModel(model);
}

void cafeteriaactualadmin::on_pushButton_7_clicked()
{
    Ajout_Produit* b= new Ajout_Produit();
    b->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    b->show();
}

void cafeteriaactualadmin::update_label()
{
    data=A.read_from_arduino();
    if(data=="1")
    {        QPixmap p(40,40);
        p.load ("C:/Users/Fares/Desktop/SmartU/Icons/fire.png");

        QIcon icon(p);
        QSystemTrayIcon n(icon);
        n.setVisible(true);
        n.showMessage("Fire Alarm Activated","something is burning",icon,3000);
        qDebug()<<"FAMA GAZ";

    }
    else if (data=="0")
    {qDebug()<<"FAMECH GAZ";
    }
}

void cafeteriaactualadmin::on_pushButton_10_clicked()
{
    QMessageBox::StandardButton reply;
        reply= QMessageBox::question(this,"Alarme","Voulez-vous activer l'alarme?", QMessageBox::Yes | QMessageBox::No);
    if (reply== QMessageBox::Yes)
    {
        A.write_to_arduino("1");
        qDebug()<<"You said YES.";
    }
    if (reply== QMessageBox::No)
    {
        A.write_to_arduino("0");
    }
}
