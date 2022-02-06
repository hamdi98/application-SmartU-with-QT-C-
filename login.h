#ifndef LOGIN_H
#define LOGIN_H
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDialog>
#include "mainwindow.h"
#include "connection.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr, QString login = nullptr);
    ~Login();
    int Authentification(QString login, QString mdp);
    void keyPressEvent(QKeyEvent *evt);

private slots:

    void on_loginbutton_released();

    void on_closebutton_released();

    void on_minimizebutton_released();

private:
    Ui::Login *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
};

#endif // LOGIN_H
