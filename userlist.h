#ifndef USERLIST_H
#define USERLIST_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class UserList;
}

class UserList : public QWidget
{
    Q_OBJECT

public:
    explicit UserList(QWidget *parent = nullptr);
    ~UserList();

    void SetTableView();

    void SetPayMasterAccess();

    void UpdateIdinTable();

private slots:

    void on_AddPayMaster_clicked();

    void on_AddUser_clicked();

    void on_DeleteUser_clicked();

    void UpdateTable();

    void on_Back_clicked();

private:
    Ui::UserList *ui;
    QSqlTableModel *model;
    bool PaymasterAccess;
};

#endif // USERLIST_H
