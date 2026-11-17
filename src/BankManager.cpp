#include "BankManager.h"
#include "BankException.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "StudentAccount.h"
#include <iomanip>
#include <iostream>

BankManager::BankManager()
    : customerCount(0), accountCount(0), nextCustomerId(1001),
      nextAccountNumber(10000001) {
    for (BankAccount*& account : accounts) account = nullptr;
    loadData(fileManager);
}

BankManager::~BankManager() {
    for (int i = 0; i < accountCount; ++i) delete accounts[i];
}

Customer* BankManager::findCustomer(int id) {
    for (int i = 0; i < customerCount; ++i) {
        if (customers[i].getCustomerId() == id) return &customers[i];
    }
    return nullptr;
}

BankAccount* BankManager::findAccount(const std::string& number) {
    for (int i = 0; i < accountCount; ++i) {
        if (accounts[i] != nullptr && accounts[i]->getAccountNumber() == number) {
            return accounts[i];
        }
    }
    return nullptr;
}

Customer* BankManager::registerCustomer(const std::string& name, const std::string& phone,
                                        const std::string& email, const std::string& address) {
    if (customerCount >= 50) return nullptr;

    customers[customerCount] = Customer(nextCustomerId++, name, phone, email, address);
    Customer* newCustomer = &customers[customerCount++];
    saveAll();
    return newCustomer;
}

bool BankManager::openAccount(int customerId, int accountType, double openingBalance) {
    Customer* owner = findCustomer(customerId);
    if (owner == nullptr || accountCount >= 100 || owner->getAccountCount() >= 5 ||
        openingBalance < 0.0) return false;

    const std::string number = std::to_string(nextAccountNumber++);
    BankAccount* newAccount = nullptr;

    if (accountType == 1) newAccount = new SavingsAccount(number, customerId, openingBalance);
    else if (accountType == 2) newAccount = new CurrentAccount(number, customerId, openingBalance);
    else if (accountType == 3) newAccount = new StudentAccount(number, customerId, openingBalance);
    else return false;

    if (!owner->addAccountNumber(number)) {
        delete newAccount;
        return false;
    }

    accounts[accountCount++] = newAccount;
    saveAll();
    std::cout << "Account number: " << number << '\n';
    return true;
}

bool BankManager::deposit(const std::string& number, double amount) {
    BankAccount* account = findAccount(number);
    if (account == nullptr) throw AccountNotFoundException("Account not found: " + number);
    if (!account->deposit(amount)) return false;
    saveAll();
    return true;
}

bool BankManager::withdraw(const std::string& number, double amount) {
    BankAccount* account = findAccount(number);
    if (account == nullptr) throw AccountNotFoundException("Account not found: " + number);
    if (!account->withdraw(amount)) return false;
    saveAll();
    return true;
}

bool BankManager::transfer(const std::string& fromNumber, const std::string& toNumber,
                           double amount) {
    BankAccount* source = findAccount(fromNumber);
    BankAccount* destination = findAccount(toNumber);

    if (source == nullptr || destination == nullptr) {
        throw AccountNotFoundException("Source or destination account was not found.");
    }
    if (source == destination) {
        throw BankException("Source and destination accounts must be different.");
    }
    if (amount <= 0.0) throw InvalidAmountException("Transfer amount must be greater than zero.");

    // Validate the source withdrawal first. If destination deposit fails, refund the source.
    if (!source->withdraw(amount)) return false;
    try {
        if (!destination->deposit(amount)) {
            source->deposit(amount);
            return false;
        }
    } catch (...) {
        source->deposit(amount);
        throw;
    }

    saveAll();
    return true;
}

bool BankManager::closeAccount(const std::string& number) {
    for (int i = 0; i < accountCount; ++i) {
        if (accounts[i] != nullptr && accounts[i]->getAccountNumber() == number) {
            if (accounts[i]->getBalance() != 0.0) return false;

            Customer* owner = findCustomer(accounts[i]->getOwnerCustomerId());
            if (owner != nullptr) owner->removeAccountNumber(number);

            delete accounts[i];
            for (int j = i; j < accountCount - 1; ++j) accounts[j] = accounts[j + 1];
            accounts[--accountCount] = nullptr;
            saveAll();
            return true;
        }
    }
    return false;
}

bool BankManager::loadData(FileManager& manager) {
    customerCount = manager.loadCustomers(customers, 50);
    nextCustomerId = 1001;

    for (int i = 0; i < customerCount; ++i) {
        if (customers[i].getCustomerId() >= nextCustomerId) {
            nextCustomerId = customers[i].getCustomerId() + 1;
        }
    }

    // Account object reconstruction is intentionally left for the next milestone.
    return true;
}

void BankManager::saveAll() {
    fileManager.saveCustomers(customers, customerCount);
    fileManager.saveAccounts(accounts, accountCount);
}

void BankManager::listCustomers() const {
    std::cout << "\nCUSTOMERS\n";
    for (int i = 0; i < customerCount; ++i) {
        std::cout << customers[i].getCustomerId() << " | " << customers[i].getName()
                  << " | Accounts: " << customers[i].getAccountCount() << '\n';
    }
}

void BankManager::listAccounts() const {
    std::cout << "\nACCOUNTS\n";
    for (int i = 0; i < accountCount; ++i) {
        if (accounts[i] != nullptr) {
            std::cout << accounts[i]->getAccountNumber() << " | "
                      << accounts[i]->getAccountType() << " | Owner ID: "
                      << accounts[i]->getOwnerCustomerId() << " | Balance: "
                      << std::fixed << std::setprecision(2) << accounts[i]->getBalance() << '\n';
        }
    }
}

void BankManager::generateDailyReport() const {
    double totalBalance = 0.0;
    for (int i = 0; i < accountCount; ++i) {
        if (accounts[i] != nullptr) totalBalance += accounts[i]->getBalance();
    }

    std::cout << "\n========== BANKCORE DAILY REPORT ==========\n"
              << "Customers: " << customerCount << "\nAccounts: " << accountCount
              << "\nTotal balance: " << std::fixed << std::setprecision(2) << totalBalance
              << "\n===========================================\n";
}
