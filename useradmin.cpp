#include "controllers.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "cryptographic.h"
#include <QDebug>

#include <QTableView>

UserAdmin::UserAdmin()
    : current_user("", 0, false), auth_attempts(0)
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

            QCryptographicHash hash_alg(QCryptographicHash::Sha512);

            while (query.next()) {
                QString salt = query.value(rec.indexOf("Salt")).toString();

                hash_alg.addData((pwd + salt).toUtf8());
                QByteArray hashed_pwd = hash_alg.result();

                QString local_name = query.value(rec.indexOf("Name")).toString();
                if (hashed_pwd == query.value(rec.indexOf("Pwd")).toByteArray())  {
                    current_user = User(
                        name,
                        query.value(rec.indexOf("rowid")).toULongLong(),
                        query.value(rec.indexOf("Active")).toBool()
                    );
                    qDebug() << "YEAH";

                    if (current_user.get_name() == "admin") {
                        qDebug() << "ADMIN";
                        qDebug() << current_user.get_uid();
                        current_user.set_as_admin();
                    }

                    return true;
                }
            }
        }
    }
    auth_attempts++;
    if (auth_attempts == MAX_AUTH_ATTEMPTS) {
        exit(0);
    }
    return false;
}

bool UserAdmin::change_pwd(QString old_pwd, QString new_pwd)
{
    if (authentification(current_user.get_name(), old_pwd)) {
        QSqlQuery query;
        CryptographicHash hash_alg(QCryptographicHash::Sha512);
        QString salt = hash_alg.generate_salt();
        hash_alg.addData((new_pwd + salt).toUtf8());
        query.prepare("UPDATE Users SET Pwd = (:pwd), Salt = (:salt)"
                      "WHERE rowid = :rowid");
        query.bindValue(":pwd", hash_alg.result());
        query.bindValue(":salt", salt);
        query.bindValue(":rowid", current_user.get_uid());
        query.exec();
        return true;
    }
    else {
        return false;
    }
}

QSqlTableModel* UserAdmin::query_users()
{
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("Users");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    return model;
}
