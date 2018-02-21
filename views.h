#ifndef VIEWS_H
#define VIEWS_H

#include <QMainWindow>
#include <QDialog>
#include "controllers.h"

namespace Ui {
class FriendlyMain;
class FriendlyLogin;
}

class FriendlyMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit FriendlyMain(QWidget *parent = 0);
    ~FriendlyMain();

    void open_login();


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

private:
    Ui::FriendlyLogin *ui;
};

#endif // VIEWS_H
