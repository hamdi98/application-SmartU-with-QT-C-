#include "demandestaff.h"
#include "ui_demandestaff.h"

demandestaff::demandestaff(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::demandestaff)
{
    ui->setupUi(this);
    refreshtabledemande();
    refreshtablemat();
    refreshtablestock();
    ui->lineEdit_11->setValidator( new QIntValidator(0,100,this));
    ui->lineEdit_9->setValidator( new QIntValidator(0,999999,this));
    QDate d = QDate::currentDate();
    ui->dateEdit_3->setDate(d);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
           break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
            break;
    case(-1):qDebug() << "arduino is not available";
               }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

}

demandestaff::~demandestaff()
{
    delete ui;
}

void demandestaff::refreshtabledemande()
{
    QSqlQueryModel *m = new QSqlQueryModel();
    QSqlQuery *q= new QSqlQuery();
    q->prepare("SELECT * FROM DEMANDE");
    q->exec();
    m->setQuery(*q);
    m->setHeaderData(1, Qt::Horizontal, tr("Quantité"));
    m->setHeaderData(2, Qt::Horizontal, tr("ID Materiel"));
    m->setHeaderData(3, Qt::Horizontal, tr("CIN"));
    m->setHeaderData(4, Qt::Horizontal, tr("Date"));
    ui->tableView_5->setModel(m);
    ui->tableView_5->setColumnHidden(0,true);
    ui->tableView_5->setColumnWidth(1, ui->tableView_5->width()/4);
    ui->tableView_5->setColumnWidth(2, ui->tableView_5->width()/4);
    ui->tableView_5->setColumnWidth(3, ui->tableView_5->width()/4);
    ui->tableView_5->setColumnWidth(4, ui->tableView_5->width()/4);
}

void demandestaff::refreshtablestock()
{
    QSqlQueryModel *m = new QSqlQueryModel();
    QSqlQuery *q= new QSqlQuery();
    q->prepare("SELECT * FROM STOCK");
    q->exec();
    m->setQuery(*q);
    m->setHeaderData(0, Qt::Horizontal, tr("Nom"));
    ui->tableView_8->setModel(m);
    ui->tableView_8->setColumnWidth(0, ui->tableView_8->width());
}

void demandestaff::refreshtablemat()
{
    QSqlQueryModel *m = new QSqlQueryModel();
    QSqlQuery *q= new QSqlQuery();
    q->prepare("SELECT * FROM MATERIEL");
    q->exec();
    m->setQuery(*q);
    m->setHeaderData(1, Qt::Horizontal, tr("Quantité"));
    m->setHeaderData(2, Qt::Horizontal, tr("Date"));
    m->setHeaderData(3, Qt::Horizontal, tr("Nom du Stock"));
    m->setHeaderData(4, Qt::Horizontal, tr("Nom du Materiel"));
    ui->tableView_6->setModel(m);
    ui->tableView_6->setColumnHidden(0,true);
    ui->tableView_6->setColumnWidth(1, ui->tableView_6->width()/4);
    ui->tableView_6->setColumnWidth(2, ui->tableView_6->width()/4);
    ui->tableView_6->setColumnWidth(3, ui->tableView_6->width()/4);
    ui->tableView_6->setColumnWidth(4, ui->tableView_6->width()/4);
}

void demandestaff::searchdemande(QString id)
{
    QSqlQueryModel *m = new QSqlQueryModel();
    QSqlQuery *q= new QSqlQuery();
    q->prepare("SELECT * FROM DEMANDE where IDDEMANDE = ?");
    q->addBindValue(id);
    q->exec();
    m->setQuery(*q);
    m->setHeaderData(1, Qt::Horizontal, tr("Quantité"));
    m->setHeaderData(2, Qt::Horizontal, tr("Date"));
    m->setHeaderData(3, Qt::Horizontal, tr("Nom du Stock"));
    m->setHeaderData(4, Qt::Horizontal, tr("Nom du Materiel"));
    ui->tableView_5->setModel(m);
    ui->tableView_5->setColumnHidden(0,true);
    ui->tableView_5->setColumnWidth(1, ui->tableView_5->width()/4);
    ui->tableView_5->setColumnWidth(2, ui->tableView_5->width()/4);
    ui->tableView_5->setColumnWidth(3, ui->tableView_5->width()/4);
    ui->tableView_5->setColumnWidth(4, ui->tableView_5->width()/4);
}
void demandestaff::on_pushButton_8_released()
{
    if(ui->lineEdit_9->text().size()!=0)
    {
        searchdemande(ui->lineEdit_9->text());
    }
    else
    {
        refreshtabledemande();
    }
}

void demandestaff::on_pushButton_15_released()
{
    if(ui->tableView_6->model()->index(ui->tableView_6->currentIndex().row(),0).data().toString().size()>0)
        {
            QString id;
            id = ui->tableView_6->model()->index(ui->tableView_6->currentIndex().row(),0).data().toString();
            Materiel *m = new Materiel();
            m->setid(id);
            m->suprimer();
            delete m;
            refreshtablemat();
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Donnes insiffisants ou errones",QMessageBox::Ok);
        }
}

void demandestaff::on_pushButton_14_released()
{
    if((ui->lineEdit_11->text().toInt()>0)&&(ui->label_28->text().size()>0)&&(ui->lineEdit_12->text().size()>0))
        {
            Materiel* m= new Materiel();
            m->setid("1");
            m->setqte(ui->lineEdit_11->text().toInt());
            m->setdate(ui->dateEdit_3->date().toString("dd/MM/yyyy"));
            m->setnom(ui->label_28->text());
            m->setnommat(ui->lineEdit_12->text());
            m->ajouter();
            delete m;
            refreshtablemat();
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Donnes insiffisants ou errones",QMessageBox::Ok);
        }
}

void demandestaff::on_pushButton_7_released()
{
    if(ui->tableView_5->model()->index(ui->tableView_5->currentIndex().row(),0).data().toInt()>0)
        {
            int id;
            id = ui->tableView_5->model()->index(ui->tableView_5->currentIndex().row(),0).data().toInt();
            Staff s;
            QString datenow;
            datenow=ui->dateEdit_3->date().toString("dd/MM/yyyy");
            s.repondre(id,false,datenow);
            refreshtabledemande();
            refreshtablemat();
            refreshtablestock();
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Donnes insiffisants ou errones",QMessageBox::Ok);
        }
}

void demandestaff::on_pushButton_6_released()
{
    if(ui->tableView_5->model()->index(ui->tableView_5->currentIndex().row(),0).data().toInt()>0)
        {
            int id;
            ui->tableView_5->selectColumn(0);
            id = ui->tableView_5->model()->index(ui->tableView_5->currentIndex().row(),0).data().toInt();
            Staff s;
            QString datenow;
            datenow=ui->dateEdit_3->date().toString("dd/MM/yyyy");
            s.repondre(id,true,datenow);
            refreshtabledemande();
            refreshtablemat();
            refreshtablestock();
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Donnes insiffisants ou errones",QMessageBox::Ok);
        }
}

void demandestaff::on_tableView_8_clicked(const QModelIndex &index)
{
    ui->label_28->setText(ui->tableView_8->model()->index(ui->tableView_8->currentIndex().row(),0).data().toString());
}


void demandestaff::on_pushButton_16_released()
{
    if(ui->label_Arduino->text()!="En attente...")
    {
        Materiel *m = new Materiel();
        m->setid("1");
        m->setqte(ui->lineEdit_11->text().toInt());
        m->setdate(ui->dateEdit_3->date().toString("dd/MM/yyyy"));
        m->setnom(ui->label_28->text());
        m->setnommat(ui->lineEdit_12->text());
        m->setrfid(ui->label_Arduino->text());
        m->ajouterArduino();
        refreshtablemat();
    }
    else
    {
        QMessageBox::warning(this,"Error","Veuillez insérer une carte avant d'ajouter le matériel associé",QMessageBox::Ok);
    }
}

void demandestaff::update_label()
{
    QByteArray temp= A.read_from_arduino();
    qDebug()<<temp;
    if(data!=temp)
    {
        data=temp;
        if((ui->label_Arduino->text()=="En attente...")||((ui->label_Arduino->text().indexOf(data)==-1)&&(ui->label_Arduino->text().size()>=15)))
        {
            ui->label_Arduino->setText("");
            qDebug() <<ui->label_Arduino->text().indexOf(data);
        }
        if(ui->label_Arduino->text().size()<15)
        {
            ui->label_Arduino->setText(ui->label_Arduino->text()+data);
        }
    }
    send();
}

void demandestaff :: send ()
{
     QString l;
     QSqlQuery q;
    QByteArray d;
   l=ui->label_Arduino->text();
   q.prepare("select * from materiel  where RFID_code = ?");
   q.addBindValue(l);
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

