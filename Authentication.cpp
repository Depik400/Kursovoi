#include "Authentification.h"
#include "registration.h"
#include "ui_Authentication.h"
#include "user.h"
#include <Mediator.h>
#include <fstream>
#include <string>
#include <QSettings>
#include <QMessageBox>
#include <QSqlError>
#include <QChar>
#include <QWidget>
#include <QFile>
#include <QDataStream>
#include <QDebug>


Password::Password(QWidget *parent) :
    QMainWindow(parent),
    passwordui(new Ui::Password)
{
    passwordui->setupUi(this);
    Count = 4;
    setAttribute(Qt::WA_DeleteOnClose);
}

Password::~Password()
{
    delete passwordui;
}

bool Password::CheckLoginAndPass(QString Login, QString Password)
{
    QSqlQuery query;
    bool Check = false;
    query.exec(QString(tr("select * from Users where login = '%1' and pass = '%2'")).arg(CodePassword(Login)).arg(CodePassword(Password)));
    qDebug() << query.lastError().text();
    while(query.next())
    {
        UserAuth.Login = CodePassword(query.value(1).toString());
        UserAuth.Password = CodePassword(query.value(2).toString());
        if(Login == UserAuth.Login && Password == UserAuth.Password)
        {
            UserAuth.FirstName = query.value(3).toString();
            UserAuth.LastName = query.value(4).toString();
            UserAuth.Group = query.value(5).toString();
            Check = true;
            break;
        }
    }
    if(!Check)
    {
        QMessageBox::warning(this,"Wrong Login or Password",tr("Your Login or Password is incorrect. You have %1 try").arg(Count-1));
        return false;
    }
    return true;
}

void Password::on_Enter_clicked()
{
    if(Count == 0)
    {
        QMessageBox::warning(this,"Warning","You must restart the program");
        exit(EXIT_FAILURE);
    }

//        QSqlQuery query;
//        QString queryt = tr("INSERT INTO Users (login,pass,firstname,lastname,team) VALUES ('%1','%2','%3','%4','%5')");
//        queryt =queryt.arg(CodePassword("admin")).arg(CodePassword("admin")).arg("admin").arg("admin").arg("Administrators");
//        query.exec(queryt);
//        qDebug() << query.lastError().text();

    QString Login = passwordui->Login->text();
    QString Password = passwordui->Pass->text();
    if(!CheckLoginAndPass(Login,Password))
    {
        passwordui->Login->setText("");
        passwordui->Pass->setText("");
        Count--;
        return;
    }
    else
    {
        QMessageBox::information(this,"Welcome",tr("Welcome %1[%2]").arg(UserAuth.FirstName,UserAuth.Group));
        emit SendToMakeWindow(UserAuth);
    }
}

void Password::ReturnUser(UserParameters &MainWindowStruct)
{
    MainWindowStruct = UserAuth;
}

void Password::on_Autentif_clicked()
{
    Registration *registration = new Registration(this);
    registration->setWindowModality(Qt::ApplicationModal);
    registration->show();
}


