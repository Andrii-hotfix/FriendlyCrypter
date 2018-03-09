#include "views.h"
#include "ui_friendlymain.h"
#include "models.h"
#include "controllers.h"
#include <QMessageBox>
#include <QTimer>
#include <QTableView>

FriendlyMain::FriendlyMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FriendlyMain),
    authAttempts(0)
{   
    ui->setupUi(this);
    setFixedSize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);

    connect(ui->HomeBtn, SIGNAL(clicked()), this, SLOT(setHomepage()));
    connect(ui->AdminBtn, SIGNAL(clicked()), this, SLOT(setAdminpage()));
    connect(ui->AdminConfirm, SIGNAL(clicked()), this, SLOT(pwdChange()));
    connect(ui->manageButton, SIGNAL(clicked()), this, SLOT(openUsersLst()));

    QThread* loginRoutine = new QThread;

    connect(loginRoutine, SIGNAL(started()), this, SLOT(openLogin()));
    loginRoutine->start();
}

FriendlyMain::~FriendlyMain()
{
    delete ui;
}

void FriendlyMain::openLogin()
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
        initialLogin->getUnameInput(),
        initialLogin->getPwdInput()
    );

    if (authentificated) {
        const QSignalBlocker blocker(initialLogin);
        initialLogin->close();
    }
    else {
        initialLogin->setError("incorrect password");
        authAttempts++;
        if (authAttempts == MAX_AUTH_ATTEMPTS) {
            close();
        }
    }
}

void FriendlyMain::setHomepage()
{
    ui->PagesStack->setCurrentIndex(0);
}

void FriendlyMain::setAdminpage()
{
    ui->PagesStack->setCurrentIndex(1);
}

void FriendlyMain::setCryptpage()
{
    ui->PagesStack->setCurrentIndex(2);
}

void FriendlyMain::setChecksumpage()
{
    ui->PagesStack->setCurrentIndex(3);
}

void FriendlyMain::pwdChange()
{
    QString newPwd = ui->NewPwdLEdit->text();
    QString confirm = ui->ConfirmLEdit->text();
    if (newPwd == confirm) {
        QString oldPwd = ui->OldPwdLEdit->text();
        bool success = adm.changePwd(oldPwd, newPwd);
        if (success) {
            ui->Alerts->setText("Successfully changed password!");
            ui->OldPwdLEdit->clear();
            ui->NewPwdLEdit->clear();
            ui->ConfirmLEdit->clear();
            // set display message only for 3 sec.
            QTimer::singleShot(3000, [&](){ ui->Alerts->setText(""); });
        } else {
            ui->Alerts->setText("Error, coluld not change password");
        }
    } else {
        ui->Alerts->setText("New password is not confirmed");
    }
}

void FriendlyMain::openUsersLst()
{
    UsersList uList;
    uList.setModel(adm.queryUsers());
    uList.exec();
}
