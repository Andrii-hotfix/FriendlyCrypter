#include "models.h"

User::User(QString name = "", unsigned long uid = 0, bool admin= false) :
    name(name),
    uid(uid),
    admin(admin) {}

User::~User() {}

QString User::getName()
{
    return name;
}

unsigned long long User::getUid()
{
    return uid;
}

bool User::isActive()
{
    return active;
}

bool User::isAdmin()
{
    return admin;
}

bool User::isPwdRestricted()
{
    return pwdRestricted;
}

void User::restrictPwd()
{
    pwdRestricted = true;
}

void User::unrestrictPwd()
{
    pwdRestricted = false;
}

void User::activate()
{
    active = true;
}

void User::deactivate()
{
    active = false;
}

void User::setAsAdmin()
{
    admin = true;
}

void User::setAsUser()
{
    admin = false;
}
