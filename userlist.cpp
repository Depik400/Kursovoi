#include "userlist.h"
#include "ui_userlist.h"
#include "registration.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <vector>

UserList::UserList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserList)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    PaymasterAccess = false;
    SetTableView();
}

UserList::~UserList()
{
    delete ui;
}

void UserList::SetTableView()
{
    model = new QSqlTableModel(this);
    model->setTable("Users");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->hideColumn(0);
}

void UserList::on_AddPayMaster_clicked()
{
    Registration *registration = new Registration(this);
    connect(registration,SIGNAL(UpdateTableInUserTools()),this,SLOT(UpdateTable()));
    registration->setWindowModality(Qt::ApplicationModal);
    registration->RegistationOnUserTools();
    registration->RegistrationForPayMaster();
    registration->show();
}

void UserList::on_AddUser_clicked()
{
    Registration *registration = new Registration(this);
    connect(registration,SIGNAL(UpdateTableInUserTools()),this,SLOT(UpdateTable()));
    registration->setWindowModality(Qt::ApplicationModal);
    registration->RegistationOnUserTools();
    registration->show();
}

void UserList::on_DeleteUser_clicked()
{
    int currentrow = ui->tableView->currentIndex().row();
    if(currentrow >= 0)
    {
        int check = QMessageBox::question(this,"Подтверждение","Вы уверены, что хотите удалить пользователя?"
                                          ,QMessageBox::Ok|QMessageBox::Cancel);
        if(check == QMessageBox::Ok)
        {
            model->removeRow(currentrow);
            UpdateTable();
        }
        else {
            return;
        }
    }
}

void UserList::UpdateIdinTable()
{
    QSqlQuery query;
    std::vector<int> IDS;
    query.exec("select id from Users");
    while(query.next())
        IDS.push_back(query.value(0).toInt());
    int count = 1;
    for(auto iter = IDS.begin();iter != IDS.end();iter++,count++)
        query.exec(QString(tr("UPDATE Users SET id = '%1' where id = '%2'").arg(count).arg(*iter)));
}

void UserList::UpdateTable()
{ 
    if(PaymasterAccess)
    {
        model->setFilter("team = 'Users'");
        ui->tableView->hideColumn(0);
        ui->tableView->hideColumn(1);
        ui->tableView->hideColumn(2);
    }
    UpdateIdinTable();
    model->select();
    ui->tableView->setModel(model);
}

void UserList::on_Back_clicked()
{
    close();
}

void UserList::SetPayMasterAccess()
{
    PaymasterAccess = true;
    ui->AddUser->setEnabled(false);ui->AddUser->setVisible(false);
    ui->DeleteUser->setEnabled(false);ui->DeleteUser->setVisible(false);
    ui->AddPayMaster->setEnabled(false); ui->AddPayMaster->setVisible(false);
    QRect rect = ui->tableView->geometry();
    rect.setHeight(320);
    ui->tableView->setGeometry(rect);
    UpdateTable();
}
