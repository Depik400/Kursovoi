#ifndef CHOOSESEATS_H
#define CHOOSESEATS_H
#include <QApplication>
#include <QDialog>
#include <QLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QStyle>
#include <QDesktopWidget>

class CustomDialog : public QDialog
{
public:
    CustomDialog(const QStringList& items)
    {
        setLayout(new QVBoxLayout());
        setWindowTitle("Выбор Места");
        label = new QLabel;
        label->setText("Выберите Место");
        layout()->addWidget(label);
        box = new QComboBox;
        box->addItems(items);
        layout()->addWidget(box);

        QPushButton* ok = new QPushButton("Подвердить");
        layout()->addWidget(ok);
        connect(ok, &QPushButton::clicked, this, [this]()
        {
           accept();
        });
    }

    QComboBox* comboBox() { return box; }

private:
    QComboBox* box;
    QLabel *label;
};

#endif // CHOOSESEATS_H
