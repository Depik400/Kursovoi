#ifndef ADDTOPLANETABLE_H
#define ADDTOPLANETABLE_H

#include <QWidget>
#include "anyStruct.h"
#include <QDate>

namespace Ui {
class AddToPlaneTable;
}

class AddToPlaneTable : public QWidget
{
    Q_OBJECT

public:
    explicit AddToPlaneTable(QWidget *parent = nullptr);
    ~AddToPlaneTable();


    void UpdateInfoInTable();

signals:
    void SendPlaneDataToTable(Plane &);

    void SendPlaneDataToUpdate(Plane &);

private slots:
    void on_Accept_clicked();

    void TakeInfoToUi(Plane &);

    void on_pushButton_clicked();


private:
    Ui::AddToPlaneTable *ui;
    Plane PlaneDate;
};

#endif // ADDTOPLANETABLE_H
