#ifndef PASSWORD_H
#define PASSWORD_H
#include "anyStruct.h"
#include <QMainWindow>
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Password;
}

class Password: public QMainWindow
{
    Q_OBJECT
public:
     explicit Password(QWidget *parent = nullptr);
    ~Password();

    bool CheckLoginAndPass(QString Login, QString Password);

    friend QDataStream &operator<<(QDataStream &stream, const UserParameters &A);

    friend QDataStream &operator>>(QDataStream &stream,UserParameters &A);

    void ReturnUser(UserParameters &);

signals:
    void SendToMakeWindow(UserParameters &);

private slots:
    void on_Enter_clicked();

    void on_Autentif_clicked();

private:
    UserParameters UserAuth;
    Ui::Password *passwordui;
    int Count;
};




#endif // PASSWORD_H
