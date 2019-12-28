#include "passengertable.h"
#include "ui_passengertable.h"
#include "addtopassengertable.h"
#include <QPalette>
#include <QDate>
#include <QInputDialog>
#include <QMessageBox>

PassengerTable::PassengerTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassengerTable)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->label->setText("");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    SetTable();
}

PassengerTable::~PassengerTable()
{
    delete ui;
}

void PassengerTable::SetTable()
{
    PassengerModel = new QSqlTableModel(this);
    PassengerModel->setTable("Passengers");
    PassengerModel->select();
    ui->tableView->setModel(PassengerModel);
    ui->tableView->hideColumn(0);
}

void PassengerTable::on_RegistrationTicket_clicked()
{
    AddToPassengerTable *RegistrationPassenger = new AddToPassengerTable();
    connect(RegistrationPassenger,SIGNAL(SendToUpdateTable()),this,SLOT(UpdateTable()));
    RegistrationPassenger->setWindowModality(Qt::ApplicationModal);
    RegistrationPassenger->show();
}

void PassengerTable::UpdateID()
{
    QSqlQuery query("select id from Passengers;");
    std::vector<int> IDS;
    int count = 1;
    while(query.next())
        IDS.push_back(query.value(0).toInt());
    for(auto iter  = IDS.begin();iter != IDS.end();iter++,count++)
        query.exec(QString(tr("UPDATE Passengers SET id = '%1' where id = '%2'").arg(count).arg(*iter)));
}

void PassengerTable::UpdateTable()
{
    PassengerModel->select();
    ui->tableView->setModel(PassengerModel);
    ui->label->setText("");
}

bool PassengerTable::CheckDate(int Index)
{
    QSqlQuery query;
    query.exec(QString(tr("select Data from Planes where id = '%1'").arg(Index)));
    query.next();
    QDate Data = query.value(0).toDate();
    if(Data < QDate::currentDate())
    {
        return false;
    }
    return true;
}

void PassengerTable::on_ReturnTicket_clicked()
{
    int currentTicket = ui->tableView->currentIndex().row() + 1;
    if(currentTicket - 1 < 0)
    {
        QMessageBox::warning(this,"Ошибка","Вы не выбрали строку");
        return;
    }
    QString Login = PassengerModel->index(ui->tableView->currentIndex().row(),1).data().toString();
    QString Password = PassengerModel->index(ui->tableView->currentIndex().row(),2).data().toString();
    QSqlQuery query;
    query.exec(QString(tr("Select * from Passengers where FirstName = '%1' and LastName = '%2'")
                       .arg(Login).arg(Password)));
    query.next();
    currentTicket = query.value(0).toInt();
    int PlaneID = query.value(4).toInt();
    int Position = query.value(6).toInt();
    if(!CheckDate(PlaneID))
        if(!QuestionToDeletePassenger())
            return;
    query.exec(QString(tr("select * from Planes where id = '%1'")).arg(PlaneID));
    query.next();
    int CountOfSeats = query.value(4).toInt() + 1;
    query.exec(QString(tr("UPDATE Planes SET FreeSeats = '%1' where id = '%2'").arg(CountOfSeats).arg(PlaneID)));
    query.exec(QString(tr("DELETE FROM Seats where PlaneID = '%1' and Seats = '%2'").arg(PlaneID).arg(Position)));
    PassengerModel->removeRow(currentTicket-1);
    ui->label->hide();
    UpdateTable();
    UpdateID();
    QMessageBox::information(this,"Возврат","Операция прошла успешно");
}

void PassengerTable::on_Back_clicked()
{
    close();
}

bool PassengerTable::QuestionToDeletePassenger()
{
    int question = QMessageBox::question(this,"Удаление","Данный рейс уже прошёл. Хотите удалить этого пользователя из базы?",QMessageBox::Ok|QMessageBox::Cancel);
    if(question == QMessageBox::Ok)
        return true;
    else {
        return false;
    }
}

void PassengerTable::on_SearchButton_clicked()
{
    if(CheckForPassenger)
    {
        bool PressOkey;
        QString User = QInputDialog::getText(this,"Поиск пассажира","Введите имя и фамилию",
                                             QLineEdit::Normal,"",&PressOkey);
        if(PressOkey)
        {
            QStringList List = User.split(" ");
            PassengerModel->setFilter(tr("FirstName = '%1' and LastName = '%2'").arg(List.at(0)).arg(List.at(1)));
            ui->SearchButton->setText("Очистить сортировку");
            CheckForPassenger = false;
            UpdateTable();
        }
    }
    else
    {
        ui->SearchButton->setText("Поиск Пассажира");
        CheckForPassenger = true;
        PassengerModel->setFilter("");
        UpdateTable();
    }
}
