#include "views.h"
#include "ui_friendlymain.h"
#include "models.h"
#include "controllers.h"
#include <QMessageBox>

#include <QSqlQuery>
#include <cryptographic.h>

FriendlyMain::FriendlyMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FriendlyMain)
{
    ui->setupUi(this);
    setFixedSize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);
}

FriendlyMain::~FriendlyMain()
{
    delete ui;
}

void FriendlyMain::open_login()
{
    FriendlyLogin initial_login(this);
    initial_login.exec();
    if (initial_login.result() == QDialog::Accepted) {
        UserAdmin adm;
        adm.authentification(
            initial_login.get_uname_input(),
            initial_login.get_pwd_input()
        );
    }
    else if (initial_login.result() == QDialog::Rejected) {
//        CryptographicHash alg(QCryptographicHash::Sha512);
//        QString salt = alg.generate_salt();
//        QString salted_pwd = initial_login.get_pwd_input() + salt;
//        alg.addData(salted_pwd.toUtf8());
//        QByteArray hashed_pwd = alg.result();
//        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//        db.setDatabaseName("friendly.db");
//        db.open();
//        QSqlQuery query;
//        QString name = initial_login.get_uname_input();
//        query.prepare("INSERT INTO Users (Name, PwdSize, Pwd, Active, PwdRestricted, Admin, Salt)"
//                      "VALUES (:name, :size, :pwd, 1, 0, 1, :salt)");
//        query.bindValue(":name", name);
//        query.bindValue(":size", initial_login.get_pwd_input().size());
//        query.bindValue(":pwd", hashed_pwd);
//        query.bindValue(":salt", salt);
//        query.exec();
        close();
    }
}
