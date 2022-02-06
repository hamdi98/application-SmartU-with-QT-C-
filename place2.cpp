#include "place2.h"
#include "ui_place2.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

place2::place2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::place2)
{
    ui->setupUi(this);
    refresh();
    int ret=A.connect_arduino();
        switch (ret) {
        case(0):qDebug()<<"arduino is available and connected to "<<A.getarduino_port_name();
            break;
        case(1):qDebug()<<"arduino is available but not connected to "<<A.getarduino_port_name();
            break;
        case(-1):qDebug()<<"arduino is not available";
        }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(on_reserverplace_clicked()));
}

place2::~place2()
{
    delete ui;
}
void place2::refresh()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT * FROM PLACE");
    query->exec();
    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(*query);
    ui->tableView->setModel(model);
}

void place2::on_reserverplace_clicked()
{
    data=A.read_from_arduino();
    QSqlQuery *query = new QSqlQuery();
    if(data=="1")
    {
        query->prepare("UPDATE PLACE SET ETAT='Indisponible'");
    }
    else
    {
        query->prepare("UPDATE PLACE SET ETAT='Disponible'");
    }
    query->exec();
    refresh();
}

void place2::on_pushButton_2_clicked()
{
    A.write_to_arduino("1");
}
