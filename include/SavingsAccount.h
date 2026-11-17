#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "BankAccount.h"

class SavingsAccount : public BankAccount {
private:
    double interestRate;
    double minimumBalance;

public:
    SavingsAccount(const std::string& number, int ownerId, double openingBalance);
    bool withdraw(double amount) override;
    std::string getAccountType() const override;
    double calculateInterest() const;
};

#endif // SAVINGS_ACCOUNT_H
