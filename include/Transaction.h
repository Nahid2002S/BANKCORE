#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "BankSystemTypes.h"
#include <string>

class Transaction {
private:
    std::string transactionId;
    std::string dateTime;
    std::string sourceAccount;
    std::string destinationAccount;
    TransactionType type;
    double amount;
    double balanceAfter;

public:
    Transaction();
    Transaction(const std::string& id, TransactionType type, double amount,
                const std::string& source, const std::string& destination,
                double balanceAfter);

    std::string getReceipt() const;
    double getAmount() const;
};

#endif // TRANSACTION_H
