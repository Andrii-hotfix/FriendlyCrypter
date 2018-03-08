#include "views.h"
#include "ui_userslist.h"
#include <QDialogButtonBox>
#include <QPushButton>

UsersList::UsersList(QWidget *parent) :
    QDialog(parent), ui(new Ui::UsersList), table(nullptr)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), this, SLOT(submit()));
}

UsersList::~UsersList()
{
    delete ui;
}

void UsersList::set_model(QSqlTableModel *model)
{
    table = model;
    ui->UsersListView->setModel(model);
    connect(ui->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked()), table, SLOT(revertAll()));
    // hide password column
    ui->UsersListView->hideColumn(2);
    // hide salt column
    ui->UsersListView->hideColumn(5);
    // set correct geometry
    QHeaderView* hHeader = ui->UsersListView->horizontalHeader();
    QHeaderView* vHeader = ui->UsersListView->verticalHeader();
    setFixedWidth(hHeader->length() + vHeader->width() + 18);
}

void UsersList::submit()
{
    table->database().transaction();
    if (table->submitAll()) {
        table->database().commit();
    }
    else {
        table->database().rollback();
        qDebug() << "Error commiting database";
    }
}
