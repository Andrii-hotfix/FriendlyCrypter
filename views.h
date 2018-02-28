#define VIEWS_H

#include <QMainWindow>
#include <QDialog>
#include <QSqlQueryModel>
#include "controllers.h"
#include "models.h"

#define MAINWINDOW_WIDTH 585
#define MAINWINDOW_HEIGHT 385

namespace Ui {
class FriendlyMain;
class FriendlyLogin;
class UsersList;
}

class FriendlyMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit FriendlyMain(QWidget *parent = 0);
    ~FriendlyMain();

    void open_login();

    UserAdmin adm;

public slots:
    void set_HomePage();
    void set_AdminPage();
    void set_CryptPage();
    void set_CheckSumPage();
    void pwd_change();
    void open_users_lst();
    void authentificate();

private:
    Ui::FriendlyMain *ui;
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
};

class UsersList : public QDialog
{
    Q_OBJECT

public:
    explicit UsersList(QWidget *parent = 0);
    ~UsersList();

    void set_model(QSqlQueryModel *model);

private:
    Ui::UsersList *ui;
};

