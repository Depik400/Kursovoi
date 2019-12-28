#include "addtoplanetable.h"
#include "ui_addtoplanetable.h"
#include <QDate>
#include <QSqlQuery>
#include <QMessageBox>
#include <QValidator>

AddToPlaneTable::AddToPlaneTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddToPlaneTable)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->SeatsLine->setValidator(new QIntValidator(0,900,this));
    setAttribute(Qt::WA_DeleteOnClose);
}

AddToPlaneTable::~AddToPlaneTable()
{
    delete ui;
}

void AddToPlaneTable::on_Accept_clicked()
{


    if(!ui->ModelLine->text().isEmpty() && !ui->NuberLine->text().isEmpty())
    {
        PlaneDate.Model = ui->ModelLine->text();
        PlaneDate.Number = ui->NuberLine->text();
        PlaneDate.Date = ui->dateEdit->date();
        PlaneDate.Seats = ui->SeatsLine->text();
        PlaneDate.FirstPlace = ui->FirstPlaceLine->text();
        PlaneDate.SecondPlace = ui->SeconPlaceLine->text();
        if(PlaneDate.Row == -1)
        {
            emit SendPlaneDataToTable(PlaneDate);
            close();
        }
        else
        {
            UpdateInfoInTable();
        }
    }
    else {
        QMessageBox::warning(this,"Ошибка","Заполните все поля");
    }
}

void AddToPlaneTable::TakeInfoToUi(Plane &Temp)
{
    PlaneDate.Row = Temp.Row;
    ui->ModelLine->setText(Temp.Model);
    ui->NuberLine->setText(Temp.Number);
    ui->dateEdit->setDate(Temp.Date);
    ui->SeatsLine->setText(Temp.Seats);
    ui->FirstPlaceLine->setText(Temp.FirstPlace);
    ui->SeconPlaceLine->setText(Temp.SecondPlace);
}
    void AddToPlaneTable::UpdateInfoInTable()
    {
        emit SendPlaneDataToUpdate(PlaneDate);
        close();
    }

    void AddToPlaneTable::on_pushButton_clicked()
    {
        close();
    }
