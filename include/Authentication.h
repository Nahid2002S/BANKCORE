#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "BankSystemTypes.h"
#include <string>

class Authentication {
private:
    std::string username;
    std::string passwordHash;
    UserRole role;
    int customerId;
    int failedAttempts;

public:
    Authentication();
    Authentication(const std::string& username, const std::string& password,
                   UserRole role, int customerId = -1);

    bool login(const std::string& username, const std::string& password);
    void logout();
    bool verifyPIN(const std::string& pin) const;
    bool changePassword(const std::string& oldPassword, const std::string& newPassword);
    bool isAdmin() const;
};

#endif // AUTHENTICATION_H
