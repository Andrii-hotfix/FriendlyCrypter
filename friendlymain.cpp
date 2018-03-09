#include "views.h"
#include "ui_friendlymain.h"
#include "models.h"
#include "controllers.h"
#include <QMessageBox>
#include <QTimer>
#include <QTableView>

FriendlyMain::FriendlyMain(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FriendlyMain), auth_attempts(0)
{   
    ui->setupUi(this);
    setFixedSize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);

    connect(ui->HomeBtn, SIGNAL(clicked()), this, SLOT(set_HomePage()));
    connect(ui->AdminBtn, SIGNAL(clicked()), this, SLOT(set_AdminPage()));
    connect(ui->AdminConfirm, SIGNAL(clicked()), this, SLOT(pwd_change()));
    connect(ui->manageButton, SIGNAL(clicked()), this, SLOT(open_users_lst()));

    QThread* loginRoutine = new QThread;

    connect(loginRoutine, SIGNAL(started()), this, SLOT(open_login()));
    loginRoutine->start();
}

FriendlyMain::~FriendlyMain()
{
    delete ui;
}

void FriendlyMain::open_login()
{
    FriendlyLogin* initialLogin = new FriendlyLogin(this);
    connect(initialLogin, SIGNAL(accepted()), this, SLOT(authentificate()));
    connect(initialLogin, SIGNAL(rejected()), this, SLOT(close()));
    initialLogin->exec();
}

void FriendlyMain::authentificate()
{
    FriendlyLogin* initialLogin = qobject_cast<FriendlyLogin*>(sender());
    bool authentificated = adm.authentification(
        initialLogin->get_uname_input(),
        initialLogin->get_pwd_input()
    );

    if (authentificated) {
        const QSignalBlocker blocker(initialLogin);
        initialLogin->close();
    }
    else {
        initialLogin->set_error("incorrect password");
        auth_attempts++;
        if (auth_attempts == MAX_AUTH_ATTEMPTS) {
            close();
        }
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
    QString newPwd = ui->NewPwdLEdit->text();
    QString confirm = ui->ConfirmLEdit->text();
    if (newPwd == confirm) {
        QString oldPwd = ui->OldPwdLEdit->text();
        bool success = adm.change_pwd(oldPwd, newPwd);
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
    u_list.set_model(adm.query_users());
    u_list.exec();
}
