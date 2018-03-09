#include "views.h"
#include "ui_pwdset.h"

PwdSet::PwdSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PwdSet),
    failed(false),
    errLabel(new QLabel)
{
    ui->setupUi(this);
    ui->PwdLEdit->setEchoMode(QLineEdit::Password);
    ui->ConfirmLEdit->setEchoMode(QLineEdit::Password);
}

PwdSet::~PwdSet()
{
    delete ui;
}

QString PwdSet::getNameInput()
{
    return ui->NameLEdit->text();
}

QString PwdSet::getPwdInput()
{
    return ui->PwdLEdit->text();
}

QString PwdSet::getConfirmInput()
{
    return ui->ConfirmLEdit->text();
}

void PwdSet::setErr(QString err)
{
    if (!failed) {
        errLabel->setText(err);
        errLabel->setAlignment(Qt::AlignRight);
        errLabel->setAccessibleName("ErrLbl");
        ui->EditVL->addWidget(errLabel);
        failed = true;
    } else {
        errLabel->setText(err);
    }
}
