#include "views.h"
#include "ui_userslist.h"

UsersList::UsersList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersList)
{
    ui->setupUi(this);
}

UsersList::~UsersList()
{
    delete ui;
}

void UsersList::set_model(QSqlQueryModel *model)
{
    ui->UsersListView->setModel(model);
}
