#ifndef ADDTOPASSENGERTABLE_H
#define ADDTOPASSENGERTABLE_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class AddToPassengerTable;
}

class AddToPassengerTable : public QWidget
{
    Q_OBJECT

public:
    explicit AddToPassengerTable(QWidget *parent = nullptr);
    ~AddToPassengerTable();

    void SetTableModel();

    void AddPassenger(int);

    int FindTruePassengerID(int);

    int FindTruePlaneID(int);

    void SetComboBoxItems();

    void UpdateTable();

    void SearchAtOnePlaceToPlace();

signals:
    void SendToUpdateTable();

private slots:
    void on_exit_clicked();

    void on_RegistrationPassenger_clicked();

    void on_SortUser_clicked();

    void on_SortPlane_clicked();

private:
    Ui::AddToPassengerTable *ui;
    QSqlTableModel *PlaneModel;
    QSqlTableModel *UserModel;
    bool CheckSortUser = true;
};

#endif // ADDTOPASSENGERTABLE_H
