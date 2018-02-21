#include "models.h"

File::File(unsigned long fid, QString path, User file_user)
    : fid(fid), path(path), file_user(file_user) {}

File::~File() {}

unsigned long File::get_fid()
{
    return fid;
}

QString File::get_path()
{
    return path;
}

User File::get_user()
{
    return file_user;
}
