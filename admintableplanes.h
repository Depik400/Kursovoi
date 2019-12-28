#ifndef ADMINTABLEPLANES_H
#define ADMINTABLEPLANES_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "anyStruct.h"

namespace Ui {
class AdminTablePlanes;
}

class AdminTablePlanes : public QDialog
{
    Q_OBJECT

public:
    explicit AdminTablePlanes(QWidget *parent = nullptr);
    ~AdminTablePlanes();

    void SetModelView();

     void UpdateTable();

     void MakeWindowForPayMaster();

     void UpdateRowId();

signals:
     void ChangeTableData(Plane &);

private slots:
    void on_Back_clicked();

    void on_AddRow_clicked();

    void on_DeleteRow_clicked();

    void SendPlaneDataToTable(Plane &);

    void on_ChangeRow_clicked();

    void PlaneDataToUpdate(Plane &);


    void on_SortRow_clicked();

private:
    Ui::AdminTablePlanes *ui;
    QSqlTableModel *Model;
};

#endif // ADMINTABLEPLANES_H
