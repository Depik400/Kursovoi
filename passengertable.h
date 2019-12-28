#ifndef PASSENGERTABLE_H
#define PASSENGERTABLE_H

#include <QWidget>
#include "anyStruct.h"
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class PassengerTable;
}

class PassengerTable : public QWidget
{
    Q_OBJECT

public:
    explicit PassengerTable(QWidget *parent = nullptr);
    ~PassengerTable();

    void SetTable();

    bool CheckDate(int);

    void UpdateID();

    bool QuestionToDeletePassenger();

private slots:
    void on_RegistrationTicket_clicked();

    void UpdateTable();

    void on_ReturnTicket_clicked();

    void on_Back_clicked();

    void on_SearchButton_clicked();

private:
    Ui::PassengerTable *ui;
    QSqlTableModel *PassengerModel;
    bool CheckForPassenger = true;
};

#endif // PASSENGERTABLE_H
