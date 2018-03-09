#include "views.h"
#include "ui_friendlylogin.h"
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>

FriendlyLogin::FriendlyLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendlyLogin),
    failed(false)
{
    ui->setupUi(this);    
}

FriendlyLogin::~FriendlyLogin()
{
    delete ui;
}

QString FriendlyLogin::getPwdInput()
{
    return ui->PwdLEdit->text();
}

QString FriendlyLogin::getUnameInput()
{
    return ui->UnameLEdit->text();
}

void QDialog::accept()
{
    setResult(QDialog::Accepted);
    emit accepted();
}

void FriendlyLogin::setError(QString err)
{
    if (!failed) {
        QLabel* errLabel = new QLabel;
        errLabel->setText(err);
        errLabel->setAlignment(Qt::AlignRight);
        errLabel->setAccessibleName("ErrLbl");
        ui->LoginVL->addWidget(errLabel);
        failed = true;
    }
}


