#include "views.h"
#include "ui_friendlylogin.h"
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>

FriendlyLogin::FriendlyLogin(QWidget *parent)
    : QDialog(parent), failed(false), ui(new Ui::FriendlyLogin)
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

void FriendlyLogin::set_error(QString err)
{
    if (!failed) {
        QLabel* err_label = new QLabel;
        err_label->setText(err);
        err_label->setAlignment(Qt::AlignRight);
        err_label->setAccessibleName("ErrLbl");
        ui->LoginVL->addWidget(err_label);
        failed = true;
    }
}


