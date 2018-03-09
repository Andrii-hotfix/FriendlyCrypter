#include "views.h"
#include "ui_pwdset.h"

PwdSet::PwdSet(QWidget *parent)
    : QDialog(parent), ui(new Ui::PwdSet), failed(false)
{
    ui->setupUi(this);
    ui->PwdLEdit->setEchoMode(QLineEdit::Password);
    ui->ConfirmLEdit->setEchoMode(QLineEdit::Password);
}

PwdSet::~PwdSet()
{
    delete ui;
}

QString PwdSet::get_pwd_input()
{
    return ui->PwdLEdit->text();
}

QString PwdSet::get_confirm_input()
{
    return ui->ConfirmLEdit->text();
}

void PwdSet::setErr(QString err)
{
    if (!failed) {
        QLabel* errLabel = new QLabel;
        errLabel->setText(err);
        errLabel->setAlignment(Qt::AlignRight);
        errLabel->setAccessibleName("ErrLbl");
        ui->EditVL->addWidget(errLabel);
        failed = true;
    }
}
