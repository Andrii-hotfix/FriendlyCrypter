#ifndef MODELS_H
#define MODELS_H

#include <QString>
#include <QSqlTableModel>

class User
{
private:
    QString name;
    unsigned long pwdSize;
    unsigned long long uid;
    bool active;
    bool pwdRestricted;
    bool admin;

public:
    User(QString name = "Noname", unsigned long uid = 0, bool admin = false);
    ~User();

    QString getName();
    unsigned long long getUid();
    bool isActive();
    bool isAdmin();
    bool isPwdRestricted();

    void restrictPwd();
    void unrestrictPwd();
    void activate();
    void deactivate();
    void setAsAdmin();
    void setAsUser();
};

class File
{
private:
    QString path;
    User fileUser;
    unsigned long fid;

public:
    File(unsigned long, QString, User);
    ~File();

    unsigned long getFid();
    QString getPath();
    User getUser();
};

#endif // MODELS_H
