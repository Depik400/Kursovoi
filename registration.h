#ifndef REGISTRATION_H
#define REGISTRATION_H
#include "anyStruct.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QSqlDatabase>

namespace Ui {
class Registration;
}

class Registration : public QMainWindow
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

    friend QDataStream &operator<<(QDataStream &stream, const UserParameters &A);

    friend QDataStream &operator>>(QDataStream &stream,UserParameters &A);

    bool RegistrationDataCheck();

    void RegistrationForPayMaster();

    void RegistationOnUserTools();

signals:

    void UpdateTableInUserTools();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Registration *ui;
    UserParameters UserInfo;
    QString DefaultGroup;
    QString Tools;
};

#endif // REGISTRATION_H
