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

void UsersList::set_model(QSqlTableModel *model)
{
    ui->UsersListView->setModel(model);
    // hide password column
    ui->UsersListView->hideColumn(2);
    // hide salt column
    ui->UsersListView->hideColumn(5);
    // set correct geometry
    QHeaderView* hHeader = ui->UsersListView->horizontalHeader();
    QHeaderView* vHeader = ui->UsersListView->verticalHeader();
    setFixedWidth(hHeader->length() + vHeader->width() + 18);
}
