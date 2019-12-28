#include "anyStruct.h"

QDataStream &operator<<(QDataStream &stream,const UserParameters &A)
{
    stream << A.Login;
    stream << A.Password;
    stream << A.FirstName;
    stream << A.LastName;
    stream << A.Group;
    return stream;
}

QDataStream &operator>>(QDataStream &stream,UserParameters &A)
{
    stream >> A.Login;
    stream >> A.Password;
    stream >> A.FirstName;
    stream >> A.LastName;
    stream >> A.Group;
    return stream;
}

QString CodePassword(QString string)
{
    quint32 key = 073; //шифр
    QString retStr(string.length());
    for(int i = 0; i < string.length(); i++)
    {
        retStr[i] = QChar(string.at(i).unicode() ^ key);
    }
    return retStr;
}
