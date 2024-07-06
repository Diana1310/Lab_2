#ifndef INSERTINFORMATION_H
#define INSERTINFORMATION_H

#include <QDialog>

namespace Ui {
class insertinformation;
}

class insertinformation : public QDialog
{
    Q_OBJECT

public:
    explicit insertinformation(QWidget *parent = nullptr);
    ~insertinformation();

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::insertinformation *ui;

signals:
    void databaseUpdated();
};

#endif // INSERTINFORMATION_H
