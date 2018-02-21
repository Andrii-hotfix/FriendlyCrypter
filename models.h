#ifndef MODELS_H
#define MODELS_H

#include <QString>

class User
{
private:
    QString name;
    unsigned long pwd_size;
    unsigned long uid;
    bool active;
    bool pwd_restricted;
    bool admin;

public:
    User(QString, unsigned long, bool);
    ~User();

    QString get_name();
    unsigned long get_uid();
    bool is_active();
    bool is_admin();
    bool is_pwd_restricted();

    void restrict_pwd();
    void unrestrict_pwd();
    void activate();
    void deactivate();
    void set_as_admin();
    void set_as_user();
};

class File
{
private:
    QString path;
    User file_user;
    unsigned long fid;

public:
    File(unsigned long, QString, User);
    ~File();

    QString get_file_user();
    QString get_path();
    User get_user();
};

#endif // MODELS_H
