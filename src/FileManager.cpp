#include "FileManager.h"
#include "BankException.h"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

FileManager::FileManager()
    : customerFile("data/customers.txt"), accountFile("data/accounts.txt"),
      transactionFile("data/transactions.txt") {
    std::filesystem::create_directories("data");
}

bool FileManager::saveCustomers(const Customer customers[], int count) const {
    std::ofstream file(customerFile);
    if (!file) throw FileException("Unable to open customer file for writing.");

    for (int i = 0; i < count; ++i) {
        file << customers[i].customerId << '|' << customers[i].fullName << '|'
             << customers[i].phone << '|' << customers[i].email << '|'
             << customers[i].address << '\n';
    }
    return static_cast<bool>(file);
}

int FileManager::loadCustomers(Customer customers[], int maxCount) const {
    std::ifstream file(customerFile);
    if (!file) return 0;

    int count = 0;
    std::string line;
    while (count < maxCount && std::getline(file, line)) {
        std::stringstream stream(line);
        std::string id, name, phone, email, address;
        if (std::getline(stream, id, '|') && std::getline(stream, name, '|') &&
            std::getline(stream, phone, '|') && std::getline(stream, email, '|') &&
            std::getline(stream, address)) {
            try {
                customers[count++] = Customer(std::stoi(id), name, phone, email, address);
            } catch (const std::exception&) {
                // Skip malformed customer records in this initial milestone.
            }
        }
    }
    return count;
}

bool FileManager::saveAccounts(BankAccount* accounts[], int count) const {
    std::ofstream file(accountFile);
    if (!file) throw FileException("Unable to open account file for writing.");

    for (int i = 0; i < count; ++i) {
        if (accounts[i] != nullptr) {
            file << accounts[i]->getAccountType() << '|' << accounts[i]->getAccountNumber()
                 << '|' << accounts[i]->getOwnerCustomerId() << '|'
                 << std::setprecision(15) << accounts[i]->getBalance() << '|'
                 << static_cast<int>(accounts[i]->getStatus()) << '\n';
        }
    }
    return static_cast<bool>(file);
}

int FileManager::loadAccounts(BankAccount* accounts[], int maxCount) const {
    // Initial milestone only: account records are counted, not yet reconstructed.
    (void)accounts;
    std::ifstream file(accountFile);
    if (!file) return 0;

    int count = 0;
    std::string line;
    while (count < maxCount && std::getline(file, line)) ++count;
    return count;
}

bool FileManager::appendTransaction(const Transaction& transaction) const {
    std::ofstream file(transactionFile, std::ios::app);
    if (!file) throw FileException("Unable to open transaction file.");
    file << transaction.getReceipt() << '\n';
    return static_cast<bool>(file);
}

bool FileManager::backupData() const {
    std::error_code error;
    if (std::filesystem::exists(customerFile)) {
        std::filesystem::copy_file(customerFile, customerFile + ".bak",
            std::filesystem::copy_options::overwrite_existing, error);
        if (error) return false;
    }

    error.clear();
    if (std::filesystem::exists(accountFile)) {
        std::filesystem::copy_file(accountFile, accountFile + ".bak",
            std::filesystem::copy_options::overwrite_existing, error);
        if (error) return false;
    }
    return true;
}
