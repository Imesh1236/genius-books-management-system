#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;
    bool isLoggedIn;

public:
    User();
    bool login(const std::string &inputUsername, const std::string &inputPassword);
    void logout();
    bool isUserLoggedIn() const;
    std::string getUsername() const;
    bool loadUsers();
};

#endif
