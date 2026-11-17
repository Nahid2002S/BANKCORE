#ifndef CURRENT_ACCOUNT_H
#define CURRENT_ACCOUNT_H

#include "BankAccount.h"

class CurrentAccount : public BankAccount {
private:
    double overdraftLimit;
    double monthlyFee;

public:
    CurrentAccount(const std::string& number, int ownerId, double openingBalance);
    bool withdraw(double amount) override;
    std::string getAccountType() const override;
    void applyMonthlyFee();
};

#endif // CURRENT_ACCOUNT_H
