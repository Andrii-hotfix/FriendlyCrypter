#include "models.h"

File::File(unsigned long fid, QString path, User file_user) :
    fid(fid),
    path(path),
    fileUser(file_user) {}

File::~File() {}

unsigned long File::getFid()
{
    return fid;
}

QString File::getPath()
{
    return path;
}

User File::getUser()
{
    return fileUser;
}
