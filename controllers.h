#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <models.h>
#include <QtSql>
#include <QSqlQueryModel>

class UserAdmin
{
private:
    User currentUser;
    QSqlDatabase sdb;

public:
    UserAdmin();
    ~UserAdmin();

    bool authentification(QString, QString);
    bool setAsAdmin(User);
    bool setAsUser(User);
    bool restrictPwd(User);
    bool unrestrictPwd(User);
    bool activate(User);
    bool deactivate(User);    
    bool addFile(QString);
    bool deleteFile(QString);
    bool encryptFile(QString);
    bool decryptFile(QString);
    bool listFiles(User);
    bool listFiles();
    bool changePwd(QString, QString);
    QSqlTableModel* queryUsers();
};

#endif // CONTROLLERS_H
