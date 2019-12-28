#ifndef ADMINS_H
#define ADMINS_H

#include "anyStruct.h"
#include <QMainWindow>
#include <QSqlDatabase>


namespace Ui {
class admins;
}

class admins : public QMainWindow
{
    Q_OBJECT

public:
    explicit admins(QWidget *parent = nullptr);
    ~admins();

void MakeUserData(UserParameters &);

signals:
void ReturnToAuth();

void MakePayMasterWin(UserParameters &);

private slots:
void on_pushButton_clicked();

void on_OpenUserList_clicked();

void on_Planes_clicked();

void on_PayMasterWindowMake_clicked();

private:
    Ui::admins *ui;
    UserParameters UserData;
};

#endif // ADMINS_H
