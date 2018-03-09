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
    void setHomepage();
    void setAdminpage();
    void setCryptpage();
    void setChecksumpage();
    void pwdChange();
    void openUsersLst();
    void authentificate();
    void openLogin();

private:
    Ui::FriendlyMain *ui;
    unsigned int authAttempts;
};

class FriendlyLogin : public QDialog
{
    Q_OBJECT

public:
    explicit FriendlyLogin(QWidget *parent = 0);
    ~FriendlyLogin();

    QString getUnameInput();
    QString getPwdInput();
    void setError(QString);

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

    void setModel(QSqlTableModel *model);
    void openPwdDialog();

private slots:
    void submit();
    void addRecord();
    void addRow();
    void rmRow();

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

    QString getPwdInput();
    QString getConfirmInput();
    void setErr(QString err);

private:
    Ui::PwdSet *ui;
    bool failed;
};

#endif // VIEWS_H

