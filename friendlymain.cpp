#include "views.h"
#include "ui_friendlymain.h"
#include "models.h"
#include "controllers.h"
#include <QMessageBox>
#include <QTimer>
#include <QTableView>

FriendlyMain::FriendlyMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FriendlyMain)
{   
    ui->setupUi(this);
    setFixedSize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);

    connect(ui->HomeBtn, SIGNAL(clicked()), this, SLOT(set_HomePage()));
    connect(ui->AdminBtn, SIGNAL(clicked()), this, SLOT(set_AdminPage()));
    connect(ui->AdminConfirm, SIGNAL(clicked()), this, SLOT(pwd_change()));
    connect(ui->manageButton, SIGNAL(clicked()), this, SLOT(open_users_lst()));
}

FriendlyMain::~FriendlyMain()
{
    delete ui;
}

void FriendlyMain::open_login()
{
    FriendlyLogin initial_login(this);
    connect(&initial_login, SIGNAL(accepted()), this, SLOT(authentificate()));
    connect(&initial_login, SIGNAL(rejected()), this, SLOT(close()));
    initial_login.exec();
}

void FriendlyMain::authentificate()
{
    FriendlyLogin* initial_login = qobject_cast<FriendlyLogin*>(sender());
    bool authentificated = adm.authentification(
        initial_login->get_uname_input(),
        initial_login->get_pwd_input()
    );

    if (authentificated) {
        const QSignalBlocker blocker(initial_login);
        initial_login->close();
    }
    else {
        qDebug() << "not authentificated";
    }
}

void FriendlyMain::set_HomePage()
{
    ui->PagesStack->setCurrentIndex(0);
}

void FriendlyMain::set_AdminPage()
{
    ui->PagesStack->setCurrentIndex(1);
}

void FriendlyMain::set_CryptPage()
{
    ui->PagesStack->setCurrentIndex(2);
}

void FriendlyMain::set_CheckSumPage()
{
    ui->PagesStack->setCurrentIndex(3);
}

void FriendlyMain::pwd_change()
{
    QString new_pwd = ui->NewPwdLEdit->text();
    QString confirm = ui->ConfirmLEdit->text();
    if (new_pwd == confirm) {
        QString old_pwd = ui->OldPwdLEdit->text();
        bool success = adm.change_pwd(old_pwd, new_pwd);
        if (success) {
            ui->Alerts->setText("Successfully changed password!");
            ui->OldPwdLEdit->clear();
            ui->NewPwdLEdit->clear();
            ui->ConfirmLEdit->clear();
            // set display message only for 3 sec.
            QTimer::singleShot(3000, [&](){ ui->Alerts->setText(""); });
        }
        else {
            ui->Alerts->setText("Error, coluld not change password");
        }
    }
    else {
        ui->Alerts->setText("New password is not confirmed");
    }
}

void FriendlyMain::open_users_lst()
{
    UsersList u_list;
    QTableView* users_view = new QTableView;
    u_list.set_model(adm.query_users());
    u_list.exec();
}
