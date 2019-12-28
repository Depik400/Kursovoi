#include "admintableplanes.h"
#include "ui_admintableplanes.h"
#include "addtoplanetable.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QtGui>
#include <QMessageBox>

#include <QSqlError>
#include <vector>
#include <QDebug>
#include <QString>
#include <QItemDelegate>
#include <QSqlRelationalDelegate>

AdminTablePlanes::AdminTablePlanes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminTablePlanes)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    AdminTablePlanes::SetModelView();
    ui->comboBox->addItems({"По Дате","По свободным местам","Очистить"});
}

void AdminTablePlanes::SetModelView()
{
    /* Table = QSqlDatabase::addDatabase("QSQLITE");
    Table.setDatabaseName("QSLite.db");
    //
    if(Table.open())
        qDebug() << "Table Is Open";
    // */
    Model = new QSqlTableModel(this);
    Model->setTable("Planes");
    Model->select();
    //
    ui->tableView->setModel(Model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->hideColumn(0);
}

AdminTablePlanes::~AdminTablePlanes()
{
    delete ui;
}

void AdminTablePlanes::MakeWindowForPayMaster()
{
    ui->AddRow->setEnabled(false);ui->AddRow->setVisible(false);
    ui->ChangeRow->setEnabled(false);ui->ChangeRow->setVisible(false);
    ui->DeleteRow->setEnabled(false);ui->DeleteRow->setVisible(false);
    QRect Rect = ui->tableView->geometry();
    Rect.setHeight(351);
    ui->tableView->setGeometry(Rect);
}

//slots

void AdminTablePlanes::on_AddRow_clicked()
{
    AddToPlaneTable *AddToPlaneTabl = new AddToPlaneTable();
    AddToPlaneTabl->setWindowModality(Qt::ApplicationModal);
    connect(AddToPlaneTabl,SIGNAL(SendPlaneDataToTable(Plane &)),this,SLOT(SendPlaneDataToTable(Plane &)));
    AddToPlaneTabl->show();
}

void AdminTablePlanes::on_DeleteRow_clicked()
{
    int SelectedRow = ui->tableView->currentIndex().row();
    if(SelectedRow  >= 0)
    {
        int Check = QMessageBox::warning(this,"Подтверждение","Вы уверены, что хотите удалить эту запись?",QMessageBox::Ok|QMessageBox::Cancel);
        if(Check == QMessageBox::Ok)
        {
            Model->removeRow(SelectedRow);
            QMessageBox::information(this,"Успех","Вы успешно удалили запись");
        }
    }
    else
    {
        QMessageBox::warning(this,"Ошибка","Вы не выбрали ни одной строки");
    }
    UpdateRowId();
    UpdateTable();
}

void AdminTablePlanes::on_ChangeRow_clicked()
{
    Plane TempPlaneData;
    if(ui->tableView->currentIndex().row() < 0)
    {
        QMessageBox::warning(this,"Ошибка","Вы не выбрали ни одной строки");
        return;
    }
    AddToPlaneTable *ChangeAdminTablePlanes = new AddToPlaneTable();
    ChangeAdminTablePlanes->setWindowModality(Qt::ApplicationModal);
    //
    connect(this,SIGNAL(ChangeTableData(Plane &)),ChangeAdminTablePlanes,SLOT(TakeInfoToUi(Plane &)));
    connect(ChangeAdminTablePlanes,SIGNAL(SendPlaneDataToUpdate(Plane &)),this,SLOT(PlaneDataToUpdate(Plane &)));
    //
    TempPlaneData.Row = ui->tableView->currentIndex().row() + 1;
    TempPlaneData.Model = Model->index(ui->tableView->currentIndex().row(),1).data().toString();
    TempPlaneData.Number = Model->index(ui->tableView->currentIndex().row(),2).data().toString();
    TempPlaneData.Date =Model->index(ui->tableView->currentIndex().row(),3).data().toDate();
    TempPlaneData.Seats = Model->index(ui->tableView->currentIndex().row(),4).data().toString();
    TempPlaneData.FirstPlace = Model->index(ui->tableView->currentIndex().row(),5).data().toString();
    TempPlaneData.SecondPlace = Model->index(ui->tableView->currentIndex().row(),6).data().toString();
    //
    emit ChangeTableData(TempPlaneData);
    ChangeAdminTablePlanes->show();
}

void AdminTablePlanes::SendPlaneDataToTable(Plane &TempPlaneData)
{
    QSqlQuery query;
    query.exec("select * from Planes;");
    query.last();
    int id = query.value(0).toInt() + 1;
    //
    QString str("INSERT INTO Planes (id,Model,Number,Data,Seats,First_Place,Second_Place,FreeSeats) VALUES ('%1','%2','%3','%4','%5','%6','%7','%8');");
    str = str.arg(id).arg(TempPlaneData.Model).arg(TempPlaneData.Number).arg(TempPlaneData.Date.toString("yyyy-MM-dd"))
                                              .arg(TempPlaneData.Seats).arg(TempPlaneData.FirstPlace).arg(TempPlaneData.SecondPlace)
                                               .arg(TempPlaneData.Seats);
    query.exec(str);
    qDebug() << query.lastError().text();
    UpdateTable();
}

void AdminTablePlanes::UpdateRowId()
{
    QSqlQuery query("select id from Planes;");
    std::vector<int> IDS;
    int count = 1;
    while(query.next())
        IDS.push_back(query.value(0).toInt());
    for(auto iter  = IDS.begin();iter != IDS.end();iter++,count++)
        query.exec(QString(tr("UPDATE Planes SET id = '%1' where id = '%2'").arg(count).arg(*iter)));
    //
    qDebug() << query.lastError().text();
}

void AdminTablePlanes::UpdateTable()
{
    Model->select();
    ui->tableView->setModel(Model);
}
void AdminTablePlanes::PlaneDataToUpdate(Plane &PlaneInfo)
{
    QSqlQuery query;
    QString input =tr("UPDATE Planes SET Model='%1', Number='%2',Data='%3',Seats = '%4', First_Place = '%5',Second_Place = '%6',FreeSeats = '%8' Where id='%7';");
    input = input.arg(PlaneInfo.Model).arg(PlaneInfo.Number).arg(PlaneInfo.Date.toString("yyyy-MM-dd"))
                                      .arg(PlaneInfo.Seats).arg(PlaneInfo.FirstPlace).arg(PlaneInfo.SecondPlace).arg(PlaneInfo.Row)
                                      .arg(PlaneInfo.Seats);
    query.exec(input);
    qDebug() << query.lastError().text();
    query.exec(QString(tr("DELETE from Seats where PlaneID = '%1'").arg(PlaneInfo.Row)));
    query.exec(QString(tr("Delete from Passenger where NumberOfFlight = '%1'").arg(PlaneInfo.Row)));
    UpdateTable();
}


void AdminTablePlanes::on_Back_clicked()
{
    close();
}

void AdminTablePlanes::on_SortRow_clicked()
{
    if(ui->comboBox->currentText() == "По Дате")
    {
        Model->setSort(3,Qt::DescendingOrder);
        UpdateTable();
    }
    else if(ui->comboBox->currentText() == "По свободным местам")
    {
        Model->setSort(7,Qt::DescendingOrder);
        UpdateTable();
    }
    else
    {
        Model->setSort(0,Qt::AscendingOrder);
        UpdateTable();
    }
}
