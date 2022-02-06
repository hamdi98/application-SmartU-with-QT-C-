#ifndef ACCEUIL_H
#define ACCEUIL_H
#include <QSqlQuery>
#include <QSqlError>
#include <QFrame>

namespace Ui {
class acceuil;
}

class acceuil : public QFrame
{
    Q_OBJECT

public:
    explicit acceuil(QWidget *parent = nullptr);
    ~acceuil();
    void remplir(QString login, int type);
    QString getnom();

private:
    Ui::acceuil *ui;
};

#endif // ACCEUIL_H
