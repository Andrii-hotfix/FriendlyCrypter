#include "views.h"
#include "ui_friendlymain.h"
#include "models.h"
#include "controllers.h"
#include <QMessageBox>

FriendlyMain::FriendlyMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FriendlyMain)
{
    ui->setupUi(this);
    setFixedSize(574, 411);
}

FriendlyMain::~FriendlyMain()
{
    delete ui;
}

void FriendlyMain::open_login()
{
    FriendlyLogin initial_login(this);
    initial_login.exec();
    if (initial_login.result() == QDialog::Rejected) {
        close();
    }
    else {
        UserAdmin adm;
        adm.authorize_user(
            initial_login.get_uname_input(),
            initial_login.get_pwd_input()
        );
    }
}
