#include "simpleuser.h"
#include "ui_simpleuser.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

SimpleUser::SimpleUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimpleUser)
{
    ui->setupUi(this);
}

SimpleUser::~SimpleUser()
{
    delete ui;
}

void SimpleUser::MakeUserData(UserParameters &temp)
{
    User = temp;
    ui->lineEdit->setText(QString(tr("%1 %2[%3]").arg(User.FirstName).arg(User.LastName).arg(User.Group)));
    SetTable();
}

void SimpleUser::SetTable()
{
    Model = new QSqlTableModel();
    Model->setTable("Passengers");
    Model->setFilter(QString(tr("FirstName = '%1' and LastName = '%2'").arg(User.FirstName).arg(User.LastName)));
    Model->select();
    ui->tableView->setModel(Model);
}

void SimpleUser::UpdateTable()
{
    Model->select();
    ui->tableView->setModel(Model);
}

void SimpleUser::on_Logout_clicked()
{
    emit ReturnToAuth();
    close();
}

void SimpleUser::on_ReturnTicketUserButton_clicked()
{
    if(ui->tableView->currentIndex().row() < 0)
    {
        QMessageBox::warning(this,"Ошибка","Выберите билет");
        return;
    }
    QSqlQuery query;
    QString Request = tr("UPDATE Passengers SET RefundRequest = '%1' where FirstName = '%2' and LastName = '%3'")
                        .arg("RequestToRefund").arg(User.FirstName).arg(User.LastName);
    query.exec(Request);
    qDebug() << query.lastError().text();
    UpdateTable();
}
