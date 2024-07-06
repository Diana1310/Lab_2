#ifndef DATABASE_H
#define DATABASE_H

#include <QDialog>
#include "insertinformation.h"
namespace Ui {
class Database;
}

class Database : public QDialog
{
    Q_OBJECT

public:
    explicit Database(QWidget *parent = nullptr);
    ~Database();

private slots:
    void on_flower_clicked();

    void on_composition_clicked();

    void on_informationdatabases_clicked();

    void on_addinformation_clicked();

    void on_updateinformation_clicked();

    void refreshData();

    void on_deleteall_clicked();

private:
    Ui::Database *ui;
    insertinformation *  win1;
};

#endif // DATABASE_H
