#include "paymasters.h"
#include "ui_paymasters.h"
#include "admins.h"
#include "anyStruct.h"
#include "admintableplanes.h"
#include "userlist.h"
#include "passengertable.h"

paymasters::paymasters(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::paymasters)
{
    ui->setupUi(this);
    ui->BackToAdminWindow->setVisible(false);ui->BackToAdminWindow->setEnabled(false);
}

paymasters::~paymasters()
{
    delete ui;
}

void paymasters::on_Logout_clicked()
{
    emit ReturnToAuth();
    close();
}

void paymasters::MakeUserParameters(UserParameters &Temp)
{
    User = Temp;
    ui->UserParam->setText(QString(tr("%1:[%2]")).arg(User.FirstName).arg(User.Group));
}

void paymasters::MakePaymasterFromAdmin()
{
    ui->BackToAdminWindow->setVisible(true);ui->BackToAdminWindow->setEnabled(true);
}

void paymasters::on_Planes_clicked()
{
    AdminTablePlanes *Planes = new AdminTablePlanes();
    Planes->setWindowModality(Qt::ApplicationModal);
    Planes->MakeWindowForPayMaster();
    Planes->show();
}

void paymasters::on_UserList_clicked()
{
    UserList *userlist = new UserList();
    userlist->setWindowModality(Qt::ApplicationModal);
    userlist->SetPayMasterAccess();
    userlist->show();
}

void paymasters::on_PassengerList_clicked()
{
    PassengerTable *passTable = new PassengerTable();
    passTable->setWindowModality(Qt::ApplicationModal);
    passTable->show();
}

void paymasters::on_BackToAdminWindow_clicked()
{
    emit MakeAdminWin(User);
    close();
}
