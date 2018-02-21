#include "friendlymain.h"
#include "ui_friendlymain.h"

FriendlyMain::FriendlyMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FriendlyMain)
{
    ui->setupUi(this);
}

FriendlyMain::~FriendlyMain()
{
    delete ui;
}
