#include "admins.h"
#include "ui_admins.h"
#include "registration.h"
#include "admintableplanes.h"
#include "paymasters.h"
#include "userlist.h"
#include <QtSql>
#include <QMessageBox>
#include <QTableView>

admins::admins(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admins)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

admins::~admins()
{
    delete ui;
}

void admins::MakeUserData(UserParameters &temp)
{
    UserData = temp;
    ui->UserLine->setText(tr("%1:%2").arg(UserData.FirstName,UserData.Group));
}



void admins::on_pushButton_clicked()
{
    emit ReturnToAuth();
    close();
}

void admins::on_Planes_clicked()
{
    AdminTablePlanes *TablePlanes = new AdminTablePlanes(this);
    TablePlanes->setModal(true);
    TablePlanes->show();
}


void admins::on_OpenUserList_clicked()
{
    UserList *userlist = new UserList();
    userlist->setWindowModality(Qt::ApplicationModal);
    userlist->show();
}

void admins::on_PayMasterWindowMake_clicked()
{
    emit MakePayMasterWin(UserData);
    close();
}
