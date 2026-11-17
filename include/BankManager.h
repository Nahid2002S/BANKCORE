#ifndef BANK_MANAGER_H
#define BANK_MANAGER_H

#include "Customer.h"
#include "BankAccount.h"
#include "FileManager.h"
#include <string>

class BankManager {
private:
    Customer customers[50];
    BankAccount* accounts[100];
    int customerCount;
    int accountCount;
    int nextCustomerId;
    long nextAccountNumber;
    FileManager fileManager;

    void saveAll();

public:
    BankManager();
    ~BankManager();
    BankManager(const BankManager&) = delete;
    BankManager& operator=(const BankManager&) = delete;

    Customer* registerCustomer(const std::string& name, const std::string& phone,
                              const std::string& email, const std::string& address);
    bool openAccount(int customerId, int accountType, double openingBalance);
    Customer* findCustomer(int customerId);
    BankAccount* findAccount(const std::string& accountNumber);
    bool deposit(const std::string& accountNumber, double amount);
    bool withdraw(const std::string& accountNumber, double amount);
    bool transfer(const std::string& fromAccount, const std::string& toAccount, double amount);
    bool closeAccount(const std::string& accountNumber);
    bool loadData(FileManager& fileManager);
    void generateDailyReport() const;
    void listCustomers() const;
    void listAccounts() const;
};

#endif // BANK_MANAGER_H
