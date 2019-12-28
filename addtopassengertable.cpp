#include "addtopassengertable.h"
#include "ui_addtopassengertable.h"
#include "chooseseats.h"
#include <QComboBox>
#include <QSqlQuery>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <QString>
#include <QDate>
#include <QSqlError>
#include "anyStruct.h"

AddToPassengerTable::AddToPassengerTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddToPassengerTable)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    PlaneModel = new QSqlTableModel(this);
    UserModel = new QSqlTableModel(this);
    SetComboBoxItems();
    SetTableModel();
}

AddToPassengerTable::~AddToPassengerTable()
{
    delete ui;
}

void AddToPassengerTable::SetTableModel()
{
    PlaneModel->setTable("Planes");
    PlaneModel->setFilter("");
    PlaneModel->setSort(0,Qt::AscendingOrder);
    PlaneModel->select();
    UserModel->setTable("Users");
    UserModel->setFilter("team = 'Users'");
    UserModel->select();
    ui->PlanesTable->setModel(PlaneModel);
    ui->PlanesTable->hideColumn(0);
    ui->PlanesTable->hideColumn(2);
    ui->PlanesTable->hideColumn(4);

    ui->UserTable->setModel(UserModel);
    ui->UserTable->hideColumn(0);
    ui->UserTable->hideColumn(1);
    ui->UserTable->hideColumn(2);
    ui->UserTable->hideColumn(5);
}

void AddToPassengerTable::UpdateTable()
{
    PlaneModel->select();
    ui->PlanesTable->setModel(PlaneModel);
    UserModel->select();
    ui->UserTable->setModel(UserModel);
}

void AddToPassengerTable::SetComboBoxItems()
{
    ui->PlaneSortBox->addItems({"Количество мест","Очистить","По Дате","Поиск по Месту взлёта и посадки"});
}

void AddToPassengerTable::on_RegistrationPassenger_clicked()
{
    QSqlQuery query;
    QStringList ItemList;
    int current = ui->PlanesTable->currentIndex().row() + 1;
    query.exec(QString(tr("Select Seats from Planes where id = '%1'").arg(current)));
    query.first();
    int Seats = query.value(0).toInt();
    for(int i = 1; i <= Seats;i++)
    {
        query.exec(QString(tr("select * from Seats where PlaneID = '%1' and Seats = '%2'"))
                   .arg(current).arg(i));
        query.next();
        if(query.value(0).isNull() && query.value(1).isNull())
        {
            ItemList.push_back(QVariant(i).toString());
        }
    }
    CustomDialog Dialog(ItemList);
    if (Dialog.exec() == QDialog::Accepted)
    {
        AddPassenger(QVariant(Dialog.comboBox()->currentText()).toInt());
    }
}

int AddToPassengerTable::FindTruePlaneID(int current)
{
    QSqlQuery query;
    QString Model = PlaneModel->index(current - 1,1).data().toString();
    QString Number =PlaneModel->index(current - 1,2).data().toString();
    query.exec(QString(tr("select id from Planes where Model = '%1' and Number = '%2'").arg(Model).arg(Number)));
    query.next();
    return query.value(0).toInt();
}

int AddToPassengerTable::FindTruePassengerID(int current)
{
    QSqlQuery query;
    QString FirstName = UserModel->index(current - 1,3).data().toString();
    QString LastName = UserModel->index(current - 1,4).data().toString();
    query.exec(QString(tr("select id from Users where firstname = '%1' and lastname = '%2'")
                       .arg(FirstName).arg(LastName)));
    query.next();
    return query.value(0).toInt();
}

void AddToPassengerTable::AddPassenger(int Position)
{
    QSqlQuery query;
    int CurrentPlane = FindTruePlaneID(ui->PlanesTable->currentIndex().row() + 1);
    int CurrentUser = FindTruePassengerID(ui->UserTable->currentIndex().row() + 1);
    //
    query.exec(QString(tr("INSERT INTO Seats (PlaneID,Seats) VALUES('%1','%2')").arg(CurrentPlane).arg(Position)));
    //
    Passenger Passenger;
    query.exec(QString(tr("select * from Users where id = '%1'")).arg(CurrentUser));
    query.next();
    Passenger.FirstName= query.value(3).toString();
    Passenger.LastName = query.value(4).toString();
    //
    query.exec(QString(tr("select * from Planes where id = '%1'").arg(CurrentPlane)));
    query.next();
    Passenger.Position = QVariant(Position).toString();
    Passenger.CountOfTickets = QVariant(1).toString();
    Passenger.NumberOfFlight = query.value(0).toString();
    Passenger.Date = query.value(3).toString();
    Passenger.TakeoffPlace = query.value(5).toString();
    Passenger.LandingPlace = query.value(6).toString();
    //
    int id;
    query.exec("select max(id) from Passengers");
    query.first();
    id = query.value(0).toInt() + 1;
    query.exec(QString(tr("INSERT INTO Passengers(id,FirstName,LastName,CountOfTickets,NumberOfFlight,Date,Position,"
                          "TakeoffPlace,LandingPlace) VALUES ('%1','%2','%3','%4','%5','%6','%7','%8','%9')"))
               .arg(id).arg(Passenger.FirstName).arg(Passenger.LastName).arg(Passenger.CountOfTickets).arg(Passenger.NumberOfFlight)
               .arg(Passenger.Date).arg(Passenger.Position).arg(Passenger.TakeoffPlace).arg(Passenger.LandingPlace));
    qDebug() << query.lastError().text();
    //
    query.exec(QString(tr("Select FreeSeats from Planes where id = '%1'").arg(CurrentPlane)));
    query.first();
    int Seats = query.value(0).toInt();
    query.exec(QString(tr("UPDATE Planes SET FreeSeats = '%1' where id = '%2'").arg(Seats-1).arg(CurrentPlane)));
    UpdateTable();
    emit SendToUpdateTable();
}
//#################################################################################################################################
void AddToPassengerTable::on_SortUser_clicked()
{
    if(CheckSortUser)
    {
        bool PressOkey;
        QString User = QInputDialog::getText(this,"Поиск пользователя","Введите имя и фамилию",
                                             QLineEdit::Normal,"",&PressOkey);
        if(PressOkey)
        {
            QStringList List = User.split(" ");
            UserModel->setFilter(tr("team = 'Users' and firstname = '%1' and lastname = '%2'").arg(List.at(0)).arg(List.at(1)));
            ui->SortUser->setText("Очистить сортировку");
            CheckSortUser = false;
            UpdateTable();
        }
    }
    else
    {
        ui->SortUser->setText("Найти по Имени и Фамилии");
        CheckSortUser = true;
        UserModel->setFilter("team = 'Users'");
        UpdateTable();
    }
}

void AddToPassengerTable::SearchAtOnePlaceToPlace()
{
    bool PressOkey;
    QString Places = QInputDialog::getText(this,"Поиск по месту","Введите место вылета и место посадки(Через дефис)",
                                           QLineEdit::Normal,"",&PressOkey);
    if(PressOkey)
    {
        QStringList List = Places.split("-");
        QSqlQuery query;
        PlaneModel->setFilter(tr("First_Place = '%1' and Second_Place = '%2'").arg(List.at(0)).arg(List.at(1)));
        UpdateTable();
    }
}

//#################################################################################################################################
void AddToPassengerTable::on_SortPlane_clicked()
{
    QStringList List = {"Количество мест","Очистить","По Дате","Поиск по Месту взлёта и посадки"};
    switch (List.indexOf(ui->PlaneSortBox->currentText()))
    {
        case 0:
            {
                PlaneModel->setSort(7,Qt::AscendingOrder);
                UpdateTable();
                break;
            }
        case 1:
            {
                PlaneModel->setFilter("");
                PlaneModel->setSort(0,Qt::AscendingOrder);
                UpdateTable();
                break;
            }
            case 2:
            {
                PlaneModel->setSort(3,Qt::AscendingOrder);
                UpdateTable();
                break;
            }
            case 3:
            {
                SearchAtOnePlaceToPlace();
                break;
            }
            default:
                break;
    }
}

void AddToPassengerTable::on_exit_clicked()
{
    close();
}
