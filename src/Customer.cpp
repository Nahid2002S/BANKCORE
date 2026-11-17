#include "Customer.h"
#include <iostream>

Customer::Customer() : customerId(0), accountCount(0) {}

Customer::Customer(int id, const std::string& name, const std::string& phoneNumber,
                   const std::string& emailAddress, const std::string& homeAddress)
    : customerId(id), fullName(name), phone(phoneNumber), email(emailAddress),
      address(homeAddress), accountCount(0) {}

int Customer::getCustomerId() const { return customerId; }
std::string Customer::getName() const { return fullName; }
int Customer::getAccountCount() const { return accountCount; }

std::string Customer::getAccountNumber(int index) const {
    if (index < 0 || index >= accountCount) return "";
    return accountNumbers[index];
}

bool Customer::addAccountNumber(const std::string& number) {
    if (accountCount >= 5) return false;
    accountNumbers[accountCount++] = number;
    return true;
}

bool Customer::removeAccountNumber(const std::string& number) {
    for (int i = 0; i < accountCount; ++i) {
        if (accountNumbers[i] == number) {
            for (int j = i; j < accountCount - 1; ++j) {
                accountNumbers[j] = accountNumbers[j + 1];
            }
            accountNumbers[--accountCount].clear();
            return true;
        }
    }
    return false;
}

void Customer::viewAccounts() const {
    std::cout << "Customer #" << customerId << " - " << fullName << '\n';
    for (int i = 0; i < accountCount; ++i) {
        std::cout << "  " << accountNumbers[i] << '\n';
    }
    if (accountCount == 0) std::cout << "  No accounts yet.\n";
}
