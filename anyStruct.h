#ifndef USERPARAMETERS_H
#define USERPARAMETERS_H
#include <QString>
#include <QDate>
struct UserParameters
{
    QString Login;
    QString Password;
    QString FirstName;
    QString LastName;
    QString Group;
};

struct Plane
{
    QString Model;
    QString Number;
    QDate Date;
    QString Seats;
    QString FirstPlace;
    QString SecondPlace;
    int Row = -1;
};

struct Passenger
{
    QString FirstName;
    QString  LastName;
    QString CountOfTickets;
    QString NumberOfFlight;
    QString Date;
    QString Position;
    QString TakeoffPlace;
    QString LandingPlace;
};

QDataStream &operator<<(QDataStream &stream, const UserParameters &A);
QDataStream &operator>>(QDataStream &stream,UserParameters &A);
QString CodePassword(QString);

#endif // USERPARAMETERS_H
