#include "Authentication.h"

// Classroom demonstration only: credentials are stored as plain text in this milestone.
Authentication::Authentication()
    : username("admin"), passwordHash("admin123"), role(UserRole::ADMIN),
      customerId(-1), failedAttempts(0) {}

Authentication::Authentication(const std::string& user, const std::string& password,
                               UserRole userRole, int id)
    : username(user), passwordHash(password), role(userRole), customerId(id),
      failedAttempts(0) {}

bool Authentication::login(const std::string& user, const std::string& password) {
    if (failedAttempts >= 5) return false;
    if (user == username && password == passwordHash) {
        failedAttempts = 0;
        return true;
    }
    ++failedAttempts;
    return false;
}

void Authentication::logout() {}
bool Authentication::verifyPIN(const std::string& pin) const { return pin == passwordHash; }

bool Authentication::changePassword(const std::string& oldPassword,
                                    const std::string& newPassword) {
    if (oldPassword != passwordHash || newPassword.size() < 4) return false;
    passwordHash = newPassword;
    return true;
}

bool Authentication::isAdmin() const { return role == UserRole::ADMIN; }
