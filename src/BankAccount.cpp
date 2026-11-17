#include "BankAccount.h"
#include "BankException.h"

BankAccount::BankAccount(const std::string& number, int ownerId, double openingBalance)
    : accountNumber(number), balance(openingBalance), status(AccountStatus::ACTIVE),
      ownerCustomerId(ownerId), transactionCount(0) {}

BankAccount::~BankAccount() = default;

std::string BankAccount::getAccountNumber() const { return accountNumber; }
double BankAccount::getBalance() const { return balance; }
int BankAccount::getOwnerCustomerId() const { return ownerCustomerId; }
AccountStatus BankAccount::getStatus() const { return status; }

bool BankAccount::record(const Transaction& transaction) {
    if (transactionCount >= 100) return false;
    transactions[transactionCount++] = transaction;
    return true;
}

bool BankAccount::deposit(double amount) {
    if (amount <= 0.0) {
        throw InvalidAmountException("Deposit amount must be greater than zero.");
    }
    if (status != AccountStatus::ACTIVE) {
        throw AccountFrozenException("This account is not active.");
    }

    balance += amount;
    return record(Transaction(accountNumber + "-" + std::to_string(transactionCount + 1),
                              TransactionType::DEPOSIT, amount, "", accountNumber, balance));
}

void BankAccount::freeze() { status = AccountStatus::FROZEN; }

void BankAccount::activate() {
    if (status != AccountStatus::CLOSED) status = AccountStatus::ACTIVE;
}
