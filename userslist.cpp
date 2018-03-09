#include "views.h"
#include "ui_userslist.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include "cryptographic.h"

UsersList::UsersList(QWidget *parent) :
    QDialog(parent), ui(new Ui::UsersList), table(nullptr)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), this, SLOT(submit()));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(add_row()));
    connect(ui->rmButton, SIGNAL(clicked()), this, SLOT(rm_row()));
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
    // set correct geometry (hack)
    QHeaderView* hHeader = ui->UsersListView->horizontalHeader();
    QHeaderView* vHeader = ui->UsersListView->verticalHeader();
    setFixedWidth(hHeader->length() + vHeader->width() + ui->addButton->width() / 2);
}

void UsersList::submit()
{
//    if (parent()->adm.is)
    table->database().transaction();
    if (table->submitAll()) {
        table->database().commit();
    }
    else {
        table->database().rollback();
        qDebug() << "Error commiting database";
    }
}

void UsersList::add_row()
{
    PwdSet* pwdDialog = new PwdSet(this);
    connect(pwdDialog, SIGNAL(accepted()), this, SLOT(addRecord()));
    pwdDialog->exec();
}

void UsersList::addRecord()
{
    PwdSet* pwdDialog = qobject_cast<PwdSet*>(sender());
    if (pwdDialog->get_pwd_input() == pwdDialog->get_confirm_input()) {
        pwdDialog->close();
        CryptographicHash hashAlg(QCryptographicHash::Sha512);
        QString salt = hashAlg.generate_salt();
        hashAlg.addData((pwdDialog->get_pwd_input() + salt).toUtf8());
        unsigned int row = table->rowCount();
        QSqlRecord rec = table->record();
        rec.setValue("Pwd", hashAlg.result());
        rec.setValue("Salt", salt);
        table->insertRecord(row, rec);
    } else {
        pwdDialog->setErr("Password wa not confirmed");
    }
}

void UsersList::rm_row()
{
    if (ui->UsersListView->selectionModel()->hasSelection()) {
        QModelIndexList selection = ui->UsersListView->selectionModel()->selectedRows();
        for (QModelIndex selected: selection) {
            table->removeRows(selected.row(), 1);
        }
    }
}

void UsersList::set_pwd()
{
//    PwdSet* dialog = qobject_cast<PwdSet*>(sender());
//    if (dialog->get_pwd_input() == dialog->get_confirm_input()) {
//        ui->UsersListView
//    }
}
