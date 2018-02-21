#include "models.h"

User::User(QString name = "", unsigned long uid = 0, bool admin= false)
    : name(name), uid(uid), admin(admin) {}

User::~User() {}

QString User::get_name()
{
    return name;
}

unsigned long long User::get_uid()
{
    return uid;
}

bool User::is_active()
{
    return active;
}

bool User::is_admin()
{
    return admin;
}

bool User::is_pwd_restricted()
{
    return pwd_restricted;
}

void User::restrict_pwd()
{
    pwd_restricted = true;
}

void User::unrestrict_pwd()
{
    pwd_restricted = false;
}

void User::activate()
{
    active = true;
}

void User::deactivate()
{
    active = false;
}

void User::set_as_admin()
{
    admin = true;
}

void User::set_as_user()
{
    admin = false;
}
