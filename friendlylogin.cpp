#include "views.h"
#include "ui_friendlylogin.h"
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>

FriendlyLogin::FriendlyLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendlyLogin)
{
    ui->setupUi(this);    
}

FriendlyLogin::~FriendlyLogin()
{
    delete ui;
}

QString FriendlyLogin::get_pwd_input()
{
    return ui->PwdLEdit->text();
}

QString FriendlyLogin::get_uname_input()
{
    return ui->UnameLEdit->text();
}

void QDialog::accept()
{
    setResult(QDialog::Accepted);
    emit accepted();
}
