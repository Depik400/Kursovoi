#include "Mediator.h"
#include "ui_mainwindow.h"
#include "Authentification.h"
#include "anyStruct.h"
//
#include "admins.h"
#include "simpleuser.h"
#include "paymasters.h"
//
#include "QMainWindow"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetDatabase();
    AuthOpen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MakeMainWindow(UserParameters &User)
{
    QStringList Groups;
    Groups << "Administrators" << "Users" << "Paymasters";
    switch(Groups.indexOf(User.Group))
    {
    case 0:
    {
        admins *WindowAdmin = new admins();
        connect(WindowAdmin,SIGNAL(MakePayMasterWin(UserParameters &)),this,SLOT(MakePayMasterOfAdmin(UserParameters &)));
        connect(WindowAdmin,SIGNAL(ReturnToAuth()),this,SLOT(AuthOpen()));
        WindowAdmin->MakeUserData(User);
        WindowAdmin->show();
        password->close();
        break;
    }
    case 1:
    {
        SimpleUser *WindowUser = new SimpleUser();
        connect(WindowUser,SIGNAL(ReturnToAuth()),this,SLOT(AuthOpen()));
        WindowUser->MakeUserData(User);
        WindowUser->show();
        password->close();
        break;
    }
    case 2:
    {
        paymasters *WindowPayMaster = new paymasters();
        connect(WindowPayMaster,SIGNAL(ReturnToAuth()),this,SLOT(AuthOpen()));
        connect(WindowPayMaster,SIGNAL(MakeAdminWin(UserParameters &)),this,SLOT(MakeAdminOfPayMaster(UserParameters &)));
        WindowPayMaster->MakeUserParameters(User);
        WindowPayMaster->show();
        password->close();
        break;
    }

    }
}

void MainWindow::MakePayMasterOfAdmin(UserParameters &Temp)
{
    paymasters *Master = new paymasters();
    Master->MakeUserParameters(Temp);
    Master->MakePaymasterFromAdmin();
    connect(Master,SIGNAL(ReturnToAuth()),this,SLOT(AuthOpen()));
    connect(Master,SIGNAL(MakeAdminWin(UserParameters &)),this,SLOT(MakeAdminOfPayMaster(UserParameters &)));
    Master->show();
}

void MainWindow::MakeAdminOfPayMaster(UserParameters &Temp)
{
    admins *admin = new admins();
    admin->MakeUserData(Temp);
    connect(admin,SIGNAL(MakePayMasterWin(UserParameters &)),this,SLOT(MakePayMasterOfAdmin(UserParameters &)));
    connect(admin,SIGNAL(ReturnToAuth()),this,SLOT(AuthOpen()));
    admin->show();
}

void MainWindow::AuthOpen()
{
    password = new Password();
    connect(password,SIGNAL(SendToMakeWindow(UserParameters &)),this,SLOT(MakeMainWindow(UserParameters &)));
    password->setWindowModality(Qt::ApplicationModal);
    password->show();
}

void MainWindow::SetDatabase()
{
    Table = QSqlDatabase::addDatabase("QSQLITE");
    Table.setDatabaseName("1.db");
    Table.open();
    if(Table.isOpen())
        qDebug() << "Table is open";
    QSqlQuery query;
    query.exec("select * from Users");
    query.next();
    qDebug() << query.value(4).toString();
}
