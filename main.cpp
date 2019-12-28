#include "Mediator.h"
#include <QApplication>
#include "Authentification.h"
#include "dialog.h"
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    return a.exec();
}
