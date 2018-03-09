#include "controllers.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "cryptographic.h"
#include <QDebug>

#include <QTableView>

UserAdmin::UserAdmin() :
    currentUser("", 0, false)
{
    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("friendly.db");
}

UserAdmin::~UserAdmin() {}

bool UserAdmin::authentification(QString name, QString pwd)
{
    if (sdb.open()) {
        QSqlQuery query;
        query.prepare("SELECT Name, Pwd, Active, Salt, rowid FROM Users WHERE Name = :name");
        query.bindValue(":name", name);

        if (query.exec()) {
            QSqlRecord rec = query.record();

            CryptographicHash hashAlg(QCryptographicHash::Sha512);

            while (query.next()) {
                QString salt = query.value(rec.indexOf("Salt")).toString();

                hashAlg.addData((pwd + salt).toUtf8());
                QByteArray hashedPwd = hashAlg.result();

                QString local_name = query.value(rec.indexOf("Name")).toString();
                if (hashedPwd == query.value(rec.indexOf("Pwd")).toByteArray())  {
                    currentUser = User(
                        name,
                        query.value(rec.indexOf("rowid")).toULongLong(),
                        query.value(rec.indexOf("Active")).toBool()
                    );
                    qDebug() << "YEAH";

                    if (currentUser.getName() == "admin") {
                        qDebug() << "ADMIN";
                        qDebug() << currentUser.getUid();
                        currentUser.setAsAdmin();
                    }

                    return true;
                }
            }
        }
    }
    return false;
}

bool UserAdmin::changePwd(QString old_pwd, QString new_pwd)
{
    if (authentification(currentUser.getName(), old_pwd)) {
        QSqlQuery query;
        CryptographicHash hashAlg(QCryptographicHash::Sha512);
        QString salt = hashAlg.generateSalt();
        hashAlg.addData((new_pwd + salt).toUtf8());
        query.prepare("UPDATE Users SET Pwd = (:pwd), Salt = (:salt)"
                      "WHERE rowid = :rowid");
        query.bindValue(":pwd", hashAlg.result());
        query.bindValue(":salt", salt);
        query.bindValue(":rowid", currentUser.getUid());
        query.exec();
        return true;
    } else {
        return false;
    }
}

QSqlTableModel* UserAdmin::queryUsers()
{
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("Users");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    return model;
}
