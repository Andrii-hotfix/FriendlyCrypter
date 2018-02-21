#include "friendlylogin.h"
#include "ui_friendlylogin.h"

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
