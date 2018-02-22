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
        close();
    }
}
