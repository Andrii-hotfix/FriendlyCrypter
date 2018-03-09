#ifndef VIEWS_H
#define VIEWS_H

#include <QMainWindow>
#include <QDialog>
#include <QSqlTableModel>
#include "controllers.h"
#include "models.h"

#define MAINWINDOW_WIDTH 585
#define MAINWINDOW_HEIGHT 385
#define MAX_AUTH_ATTEMPTS 3

namespace Ui {
class FriendlyMain;
class FriendlyLogin;
class UsersList;
class PwdSet;
}

class FriendlyMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit FriendlyMain(QWidget *parent = 0);
    ~FriendlyMain();    

    UserAdmin adm;

public slots:
    void set_HomePage();
    void set_AdminPage();
    void set_CryptPage();
    void set_CheckSumPage();
    void pwd_change();
    void open_users_lst();
    void authentificate();
    void open_login();

private:
    Ui::FriendlyMain *ui;
    unsigned int auth_attempts;
};

class FriendlyLogin : public QDialog
{
    Q_OBJECT

public:
    explicit FriendlyLogin(QWidget *parent = 0);
    ~FriendlyLogin();

    QString get_uname_input();
    QString get_pwd_input();
    void set_error(QString);

private:
    Ui::FriendlyLogin *ui;
    bool failed;
};

class UsersList : public QDialog
{
    Q_OBJECT

public:
    explicit UsersList(QWidget *parent = 0);
    ~UsersList();

    void set_model(QSqlTableModel *model);
    void open_pwd_dialog();

private slots:
    void submit();
    void addRecord();
    void add_row();
    void rm_row();
    void set_pwd();

private:
    Ui::UsersList *ui;
    QSqlTableModel* table;
};

class PwdSet : public QDialog
{
    Q_OBJECT

public:
    explicit PwdSet(QWidget *parent = 0);
    ~PwdSet();

    QString get_pwd_input();
    QString get_confirm_input();
    void setErr(QString err);

private:
    Ui::PwdSet *ui;
    bool failed;
};

#endif // VIEWS_H

