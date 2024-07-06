#include "insertinformation.h"
#include "ui_insertinformation.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include "database.h"
bool type_1 = false;
bool type_2 = false;
insertinformation::insertinformation(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::insertinformation)
{
    ui->setupUi(this);


}

insertinformation::~insertinformation()
{
    delete ui;
}

void insertinformation::on_radioButton_clicked()
{
    type_1 = true;
    type_2 = false;
    ui->label->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->textEdit->setVisible(true);
    ui->textEdit_2->setVisible(true);
    ui->textEdit_3->setVisible(true);
}


void insertinformation::on_radioButton_2_clicked()
{
    type_1 = false;
    type_2 = true;
    ui->label->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(false);
    ui->textEdit->setVisible(true);
    ui->textEdit_2->setVisible(true);
    ui->textEdit_3->setVisible(false);
}


void insertinformation::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");
    if(!db.open()){
        ui->textEdit->setText("Error: " + db.lastError().text());
        return;
    }
    QSqlQuery query;
    QString name="", cost = "", type = "", id = "";
    if(type_1){
        id = ui->textEdit_4->toPlainText();
        name = ui->textEdit->toPlainText();
        cost = ui->textEdit_2->toPlainText();
        type = ui->textEdit_3->toPlainText();

        query.prepare("UPDATE Flower SET id=:id, Name=:name, Type=:type, Cost=:cost WHERE id=:id");
        query.bindValue(":id", id);
        query.bindValue(":name", name);
        query.bindValue(":type", type);
        query.bindValue(":cost", cost);

        if(!query.exec()){
            qDebug() << "Error:" << query.lastError().text();
        } else {
            qDebug()<<"Successes";
            db.commit();
            db.close();
            emit databaseUpdated();
        }
    }
    if(type_2){
        id = ui->textEdit_4->toPlainText();
        name = ui->textEdit->toPlainText();
        cost = ui->textEdit_2->toPlainText();
        query.prepare("UPDATE Composition SET id=:id, Name=:name, Cost=:cost WHERE id=:id");
        query.bindValue(":id", id);
        query.bindValue(":name", name);
        query.bindValue(":cost", cost);

        if(!query.exec()){
            qDebug() << "Error:" << query.lastError().text();
        } else {
            qDebug()<<"Successes";
            db.commit();
            db.close();
            emit databaseUpdated();
        }
    }
}


void insertinformation::on_pushButton_2_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");
    if(!db.open()){
        ui->textEdit->setText("Error: " + db.lastError().text());
        return;
    }
    QSqlQuery query;
    QString id = "";
    id = ui->textEdit_4->toPlainText();

    if(type_1){
        query.prepare("DELETE FROM Flower WHERE id=:id");
        query.bindValue(":id", id);
        if(!query.exec()){
            qDebug() << "Error:" << query.lastError().text();
        } else {
            qDebug()<<"Successes";
            db.commit();
            db.close();
            emit databaseUpdated();
        }
    }
    if(type_2){
        query.prepare("DELETE FROM Composition WHERE id=:id");
        query.bindValue(":id", id);
        if(!query.exec()){
            qDebug() << "Error:" << query.lastError().text();
        } else {
            qDebug()<<"Successes";
            db.commit();
            db.close();
            emit databaseUpdated();
        }
    }
}

