#include "demandeenseignant.h"
#include "ui_demandeenseignant.h"


demandeenseignant::demandeenseignant(QWidget *parent, int id) :
    QFrame(parent),
    ui(new Ui::demandeenseignant)
{
    ui->setupUi(this);
    idens=id;
    refreshtabledemande();
    refreshtablerecus();
    refreshtablemat();
    QDate d = QDate::currentDate();
    ui->dateEdit->setDate(d);
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

demandeenseignant::~demandeenseignant()
{
    delete ui;
}

void demandeenseignant::refreshtablemat()
{
    QSqlQueryModel *m = new QSqlQueryModel();
    QSqlQuery *q= new QSqlQuery();
    q->prepare("SELECT NOMMAT FROM MATERIEL");
    q->exec();
    m->setQuery(*q);
    ui->listView->setModel(m);
}

void demandeenseignant::refreshtablerecus()
{
    QSqlQueryModel *m = new QSqlQueryModel();
    QSqlQuery *q= new QSqlQuery();
    q->prepare("SELECT * FROM RECU WHERE CINN=?");
    q->addBindValue(idens);
    q->exec();
    m->setQuery(*q);
    m->setHeaderData(1, Qt::Horizontal, tr("Quantité"));
    m->setHeaderData(2, Qt::Horizontal, tr("ID Materiel"));
    m->setHeaderData(3, Qt::Horizontal, tr("CIN"));
    m->setHeaderData(4, Qt::Horizontal, tr("Date"));
    ui->tablerecus->setModel(m);
    ui->tablerecus->setColumnHidden(0,true);
    ui->tablerecus->setColumnWidth(1, ui->tablerecus->width()/4);
    ui->tablerecus->setColumnWidth(2, ui->tablerecus->width()/4);
    ui->tablerecus->setColumnWidth(3, ui->tablerecus->width()/4);
    ui->tablerecus->setColumnWidth(4, ui->tablerecus->width()/4);
}

void demandeenseignant::refreshtabledemande()
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
    ui->tableView_3->setModel(m);
    ui->tableView_3->setColumnHidden(0,true);
    ui->tableView_3->setColumnWidth(1, ui->tableView_3->width()/4);
    ui->tableView_3->setColumnWidth(2, ui->tableView_3->width()/4);
    ui->tableView_3->setColumnWidth(3, ui->tableView_3->width()/4);
    ui->tableView_3->setColumnWidth(4, ui->tableView_3->width()/4);
}

void demandeenseignant::on_listView_clicked(const QModelIndex &index)
{
    ui->nommatlabel->setText(ui->listView->model()->index(ui->listView->currentIndex().row(),0).data().toString());
    QSqlQuery q;
    q.prepare("SELECT QTEMAT FROM MATERIEL WHERE NOMMAT=?");
    q.addBindValue(ui->nommatlabel->text());
    q.exec();
    q.first();
    ui->quantitelabel->setText(q.value(0).toString());
}

void demandeenseignant::on_pushButton_9_released()
{
    if((ui->listView->model()->index(ui->listView->currentIndex().row(),0).data().toString().size()!=0)&&(ui->qtebox->value()>0))
    {
        QSqlQuery q;
        q.prepare("SELECT IDMAT FROM MATERIEL WHERE NOMMAT=?");
        q.addBindValue(ui->nommatlabel->text());
        q.exec();
        q.first();
        Demande *dem = new Demande();
        dem->setcin(idens);
        dem->setid("1");
        dem->setidmat(q.value(0).toString());
        dem->setqte(ui->qtebox->value());
        dem->setdate(ui->dateEdit->date().toString("dd/MM/yyyy"));
        dem->afficher();
        dem->creerdemande();
        refreshtabledemande();
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Donnes insiffisants ou errones",QMessageBox::Ok);
    }
}

void demandeenseignant::on_pushButton_5_released()
{
    if(ui->tableView_3->model()->index(ui->tableView_3->currentIndex().row(),0).data().toString().size()!=0)
    {
        Demande *dem = new Demande();
        dem->setid(ui->tableView_3->model()->index(ui->tableView_3->currentIndex().row(),0).data().toString());
        dem->annuler();
        refreshtabledemande();
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Donnes insiffisants ou errones",QMessageBox::Ok);
    }
}


void demandeenseignant::on_imprimerbutton_released()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tablerecus->model()->rowCount();
    const int columnCount = ui->tablerecus->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("Recus")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
            "<center><h1>Table de Recus</h1>"
        "<table margin-left:-50px border=1 cellspacing=10 cellpadding=20>\n";
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tablerecus->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tablerecus->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tablerecus->isColumnHidden(column)) {
                QString data = ui->tablerecus->model()->data(ui->tablerecus->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table></center>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}

void demandeenseignant::on_pushButton_10_released()
{
    QSqlQuery *q = new QSqlQuery();
    q->prepare("Select IDMAT from MATERIEL where RFID_CODE = ?");
    q->addBindValue(ui->label_2->text().remove(11,4));
    qDebug() << ui->label_2->text().remove(11,4);
    qDebug() << q->exec();
    if(q->first())
    {
        Recu *r = new Recu();
        r->setcin(idens);
        r->setdate(ui->dateEdit->date().toString("dd/MM/yyyy"));
        r->setid("1");
        r->setidmat(q->value(0).toString());
        r->setqte(ui->qtebox->value());
        r->creerrecu();
        refreshtablerecus();
    }
    else
    {
        QMessageBox::warning(this,"Erreur","Carte non associée",QMessageBox::Ok);
    }
}

void demandeenseignant::update_label()
{
    QByteArray temp= A.read_from_arduino();
    if(data!=temp)
    {
        data=temp;
        if((ui->label_2->text()=="En attente...")||((ui->label_2->text().indexOf(data)==-1)&&(ui->label_2->text().size()>=15)))
        {
            ui->label_2->setText("");
            qDebug() <<data;
        }
        if(ui->label_2->text().size()<15)
        {
            ui->label_2->setText(ui->label_2->text()+data);
        }
    }
    send();
}

void demandeenseignant :: send ()
{
     QString l;
     QSqlQuery q;
    QByteArray d;
   l=ui->label_2->text();
   q.prepare("select * from materiel  where RFID_CODE = ?");
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
          d="2";
          A.write_to_arduino(d);
      }
      else
      {
          d="1";
          A.write_to_arduino(d);
      }
  }


}

