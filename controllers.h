#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <models.h>

class UserAdmin()
{
private:
    User current_user;

public:
    UserAdmin(User);
    ~UserAdmin();

    bool create_user();
    bool remove_user();
    bool set_as_admin(User);
    bool set_as_user(User);
    bool restrict_pwd(User);
    bool unrestrict_pwd(User);
    bool activate(User);
    bool deactivate(User);
    bool list_users();
    bool add_file(QString);
    bool delete_file(QString);
    bool encrypt_file(QString);
    bool decrypt_file(QString);
    bool list_files(User);
    bool list_files();

};

#endif // CONTROLLERS_H
