#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Authentification.h"
#include <QMainWindow>
#include "admins.h"
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool ChangeCheckPassword(const bool);

    void SetDatabase();

private:
    Ui::MainWindow *ui;
    Password *password;
    QSqlDatabase Table;
   // admins *WindowAdmin;

public slots:
    void MakeMainWindow(UserParameters &);

    void AuthOpen();

    void MakePayMasterOfAdmin(UserParameters &);

    void MakeAdminOfPayMaster(UserParameters &);
};

#endif // MAINWINDOW_H
