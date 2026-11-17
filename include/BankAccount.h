#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include "BankSystemTypes.h"
#include "Transaction.h"
#include <string>

class BankAccount {
protected:
    std::string accountNumber;
    double balance;
    AccountStatus status;
    int ownerCustomerId;
    Transaction transactions[100];
    int transactionCount;

    bool record(const Transaction& transaction);

public:
    BankAccount(const std::string& number, int ownerId, double openingBalance);
    virtual ~BankAccount();

    std::string getAccountNumber() const;
    double getBalance() const;
    int getOwnerCustomerId() const;
    AccountStatus getStatus() const;

    bool deposit(double amount);
    virtual bool withdraw(double amount) = 0;
    virtual std::string getAccountType() const = 0;

    void freeze();
    void activate();
};

#endif // BANK_ACCOUNT_H
