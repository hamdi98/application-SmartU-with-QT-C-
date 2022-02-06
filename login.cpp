#include "login.h"
#include "ui_login.h"


Login::Login(QWidget *parent, QString login) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->loginedit->setText(login);
}

void Login::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void Login::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

int Login::Authentification(QString login, QString mdp)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery q,qens,qetd,qadmin,qstaff;
    q.prepare("SELECT * FROM PERSONNE where MAIL=? AND MDP=?");
    q.addBindValue(login);
    q.addBindValue(mdp);
    q.exec();
    qDebug() << "Main query executed";
    if(q.first())
    {
        qens.prepare("SELECT * FROM ENSEIGNANT WHERE CINN=?");
        qens.addBindValue(q.value(0));
        qetd.prepare("SELECT * FROM ETUDIANT WHERE CINE=?");
        qetd.addBindValue(q.value(0));
        qstaff.prepare("SELECT * FROM STAFF WHERE CINS=?");
        qstaff.addBindValue(q.value(0));
        qadmin.prepare("SELECT * FROM ADMIN WHERE CINA=?");
        qadmin.addBindValue(q.value(0));
        qens.exec();
        if(qens.first())
        {
            return 3;
        }
        qetd.exec();
        if(qetd.first())
        {
            return 4;
        }
        qstaff.exec();
        if(qstaff.first())
        {
            return 2;
        }
        qadmin.exec();
        if(qadmin.first())
        {
            return 1;
        }
    }
    return 0;
}

void Login::keyPressEvent(QKeyEvent *evt)
{
    if(evt->key() == Qt::Key_Enter || evt->key() == Qt::Key_Return)
        on_loginbutton_released();
        return;
    QDialog::keyPressEvent(evt);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginbutton_released()
{
    switch(Authentification(ui->loginedit->text(),ui->mdpedit->text()))
    {
    case 0 :
    {
        QMessageBox::warning(this,"Login","Error, check your login info");
    }
    break;
    case 1 :
    {
        MainWindow *x = new MainWindow(nullptr,1,ui->loginedit->text());
        x->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        x->show();
        close();
    }
    break;
    case 2 :
    {
        MainWindow *x = new MainWindow(nullptr,2,ui->loginedit->text());
        x->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        x->show();
        close();
    }
    break;
    case 3 :
    {
        MainWindow *x = new MainWindow(nullptr,3,ui->loginedit->text());
        x->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        x->show();
        close();
    }
    break;
    case 4 :
    {
        MainWindow *x = new MainWindow(nullptr,4,ui->loginedit->text());
        x->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        x->show();
        close();
    }
    break;
    }
}

void Login::on_closebutton_released()
{
    close();
}

void Login::on_minimizebutton_released()
{
    setWindowState(Qt::WindowMinimized);
}
