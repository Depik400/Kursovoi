#ifndef PAYMASTERS_H
#define PAYMASTERS_H

#include <QMainWindow>
#include "anyStruct.h"

namespace Ui {
class paymasters;
}

class paymasters : public QMainWindow
{
    Q_OBJECT

public:
    explicit paymasters(QWidget *parent = nullptr);
    ~paymasters();

    void MakeUserParameters(UserParameters &);

    void MakePaymasterFromAdmin();

signals:
    void ReturnToAuth();

    void MakeAdminWin(UserParameters &);
private slots:
    void on_Logout_clicked();

    void on_Planes_clicked();

    void on_UserList_clicked();

    void on_PassengerList_clicked();

    void on_BackToAdminWindow_clicked();

private:
    Ui::paymasters *ui;
    UserParameters User;
};

#endif // PAYMASTERS_H
