#ifndef MYDIALOG_H
#define MYDIALOG_H
#include <QDialog>
#include <QPushButton>
#include <QMessageBox>

class QLineEdit;
class InputDialog : public QDialog {
    Q_OBJECT
private:
    QLineEdit* m_ptxtFirstName;
    QLineEdit* m_ptxtLastName;

public:
    InputDialog(QWidget* pwgt = 0);

    QString firstName() const;
    QString lastName () const;
};

class StartDialog
{

public:
    StartDialog(QWidget* pwgt = 0)
    {
    }

    void Start()
    {
        InputDialog* pInputDialog = new InputDialog;
        if (pInputDialog->exec() == QDialog::Accepted) {
            QMessageBox::information(0,
                                     "Information",
                                     "First Name: "
                                     + pInputDialog->firstName()
                                     + "\nLast Name: "
                                     + pInputDialog->lastName()
                                    );
        }
        delete pInputDialog;
    }
};

#endif // MYDIALOG_H
