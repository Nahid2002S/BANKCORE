#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "Customer.h"
#include "BankAccount.h"
#include "Transaction.h"
#include <string>

class FileManager {
private:
    std::string customerFile;
    std::string accountFile;
    std::string transactionFile;

public:
    FileManager();
    bool saveCustomers(const Customer customers[], int count) const;
    int loadCustomers(Customer customers[], int maxCount) const;
    bool saveAccounts(BankAccount* accounts[], int count) const;
    int loadAccounts(BankAccount* accounts[], int maxCount) const;
    bool appendTransaction(const Transaction& transaction) const;
    bool backupData() const;
};

#endif // FILE_MANAGER_H
