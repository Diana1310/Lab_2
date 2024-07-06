#include "registration.h"
#include "ui_registration.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include "Validator.h"
registration::registration(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registration)
{
    ui->setupUi(this);

}

registration::~registration()
{
    delete ui;
}

void registration::on_RegistrationButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");
    if(!db.open()){
        QMessageBox::critical(this, "Ошибка", "База данных не найдена "+ QString(db.lastError().text()));
        return;
    }
    QSqlQuery qry;
    QString newlogin = "";
    QString newpassword = "";
    QString newid = "";
    qry.prepare("SELECT MAX(id) FROM User");
    if(!qry.exec()){
        QMessageBox::critical(this, "Ошибка", qry.lastError().text());
        return;
    }
    if(qry.next()){
        newid = QString::number(qry.value(0).toInt() + 1);
    }

    bool isLoginValid = false;
    bool isPasswordValid = false;
    validator password;
    validator login;
    newlogin = ui->newlinelogin->text();
    newpassword = ui->newlinepassword->text();
    if (!isLoginValid || !isPasswordValid) {

        isLoginValid = login.validlogin(newlogin);
        isPasswordValid = password.validpassword(newpassword);

        if (!isLoginValid || !isPasswordValid) {
            QMessageBox::critical(this, "Ошибка проверки", "Неверные пароль или логин");
            hide();
            return;
        }
    }
    qry.prepare("SELECT COUNT(*) FROM User WHERE login = :login");
    qry.bindValue(":login", newlogin);
    qry.exec();
    if(qry.next()){
        int count = qry.value(0).toInt();
        if(count>0){
            QMessageBox::warning(this, "", "Пользователь с таким именем уже существует");
        }else{
            qry.prepare("INSERT INTO User (id, Login, Password) VALUES(:val1, :val2, :val3)");
            qry.bindValue(":val1", newid);
            qry.bindValue(":val2", newlogin);
            qry.bindValue(":val3", newpassword);
            if(!qry.exec()){
                QMessageBox::critical(this, "Ошибка", qry.lastError().text());
                return;
            }
            QMessageBox::warning(this, "Регистрация", "Вы успешно зарегестрировались");
            db.close();

            hide();
        }
    }


}

