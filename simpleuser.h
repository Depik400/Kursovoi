#ifndef SIMPLEUSER_H
#define SIMPLEUSER_H
#include "anyStruct.h"
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class SimpleUser;
}

class SimpleUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimpleUser(QWidget *parent = nullptr);
    ~SimpleUser();

    void MakeUserData(UserParameters &);

    void SetTable();

    void UpdateTable();

signals:
void ReturnToAuth();

private slots:
void on_Logout_clicked();

void on_ReturnTicketUserButton_clicked();

private:
    Ui::SimpleUser *ui;
    UserParameters User;
    QSqlTableModel *Model;
};

#endif // SIMPLEUSER_H
