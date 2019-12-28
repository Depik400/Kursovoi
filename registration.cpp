#include "registration.h"
#include "ui_registration.h"
#include "Authentification.h"
#include <QDialog>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
Registration::Registration(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    //
    DefaultGroup = "Users";
    Tools = "AuthTools";
}

Registration::~Registration()
{
    delete ui;
}

bool Registration::RegistrationDataCheck()
{
    ui->Login->setText(ui->Login->text().replace(" ",""));
    ui->Password->setText(ui->Password->text().replace(" ",""));
    if(!(ui->Login->text().isEmpty()|| ui->Password->text().isEmpty()|| ui->FirstName->text().isEmpty() || ui->LastName->text().isEmpty()))
    {
        QSqlQuery query(QString(tr("select * from Users where login = '%1'")).arg(CodePassword(ui->Login->text())));
        query.exec();
        query.first();
        if(query.value(0).isNull())
        {
            UserInfo.Login = CodePassword(ui->Login->text());
            UserInfo.Password = CodePassword(ui->Password->text());
            UserInfo.FirstName = ui->FirstName->text();
            UserInfo.LastName = ui->LastName->text();
            UserInfo.Group = DefaultGroup;
            return true;
        }
        else {
            QMessageBox::warning(this,"Ошибка","Пользователь с таким логином уже существует");
            return false;
        }
    }
    else
    {
        QMessageBox::warning(this,"Ошибка","Заполните все поля");
    }
    return false;
}

void Registration::on_pushButton_clicked()
{
    if(Registration::RegistrationDataCheck())
    {
        QSqlQuery query;
        query.exec("select max(id) from Users");
        query.first();
        int id = query.value(0).toInt() + 1;
        QString QueryString = tr("INSERT INTO Users (id,login,pass,firstname,lastname,team) VALUES('%1','%2','%3','%4','%5','%6')");
        QueryString = QueryString.arg(id).arg(UserInfo.Login).arg(UserInfo.Password)
                .arg(UserInfo.FirstName).arg(UserInfo.LastName).arg(UserInfo.Group);
        query.exec(QueryString);
        if(Tools == "UserTools")
            emit UpdateTableInUserTools();
        close();
    }
}

void Registration::RegistationOnUserTools()
{
    Tools = "UserTools";
}

void Registration::RegistrationForPayMaster()
{
    DefaultGroup = "Paymasters";
}
