#ifndef DIALOG_H
#define DIALOG_H

#include <QMainWindow>
#include <QDialog>

namespace Ui {
class dialog;
}

class dialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit dialog(QWidget *parent = nullptr);
    ~dialog();

    QString ReturnLogin();

private:
    Ui::dialog *ui;
    Ui::dialog *dialogui;
};

#endif // DIALOG_H
