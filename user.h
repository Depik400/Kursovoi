#ifndef USER_H
#define USER_H
#include <QString>

class User
{
private:
    const QString Group = "Users";
    QString Login;
    QString Password;
    QString FirstName;
    QString LastName;
public:
    User(QString L,QString P,QString FN,QString  LN)
    {
        Login = L;
        Password = P;
        FirstName = FN;
        LastName =LN;
    }
};

#endif // USER_H
