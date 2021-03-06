#include "views.h"
#include "ui_userslist.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include "cryptographic.h"
#include "models.h"

UsersList::UsersList(QWidget *parent) : QDialog(parent),
    ui(new Ui::UsersList),
    table(nullptr)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), this, SLOT(submit()));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(ui->rmButton, SIGNAL(clicked()), this, SLOT(rmRow()));
}

UsersList::~UsersList()
{
    delete ui;
}

void UsersList::setModel(QSqlTableModel *model)
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

void UsersList::addRow()
{
    PwdSet* pwdDialog = new PwdSet(this);
    connect(pwdDialog, SIGNAL(accepted()), this, SLOT(addRecord()));
    pwdDialog->exec();
}

void UsersList::addRecord()
{
    PwdSet* pwdDialog = qobject_cast<PwdSet*>(sender());
    QString name = pwdDialog->getNameInput();
    QString pwd = pwdDialog->getPwdInput();
    QString confirm = pwdDialog->getConfirmInput();
    if (pwd.isEmpty() || name.isEmpty()) {
        pwdDialog->setErr("Please fill in all fields");
    } else if (pwd == confirm) {
        QSqlQuery nameQuery;
        nameQuery.prepare("SELECT Name FROM Users WHERE Name = (:name)");
        nameQuery.bindValue(":name", name);
        nameQuery.exec();
        if (!nameQuery.next()) {
            pwdDialog->close();
            CryptographicHash hashAlg(QCryptographicHash::Sha512);
            QString salt = hashAlg.generateSalt();
            hashAlg.addData((pwd + salt).toUtf8());
            unsigned int row = table->rowCount();
            QSqlRecord rec = table->record();
            User newUser(name);
            rec.setValue("Pwd", hashAlg.result());
            rec.setValue("PwdSize", pwd.size());
            rec.setValue("Salt", salt);
            rec.setValue("Name", newUser.getName());
            rec.setValue("Active", newUser.isActive());
            rec.setValue("PwdRestricted", newUser.isPwdRestricted());
            rec.setValue("Admin", newUser.isAdmin());
            table->insertRecord(row, rec);
        } else {
            pwdDialog->setErr("This name is allredy in use");
        }
    } else {
        pwdDialog->setErr("Password was not confirmed");
    }
}

void UsersList::rmRow()
{
    if (ui->UsersListView->selectionModel()->hasSelection()) {
        QModelIndexList selection = ui->UsersListView->selectionModel()->selectedRows();
        for (QModelIndex selected: selection) {
            table->removeRows(selected.row(), 1);
        }
    }
}
