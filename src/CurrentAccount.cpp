#include "CurrentAccount.h"
#include "BankException.h"

CurrentAccount::CurrentAccount(const std::string& number, int ownerId, double openingBalance)
    : BankAccount(number, ownerId, openingBalance), overdraftLimit(1000.0), monthlyFee(10.0) {}

bool CurrentAccount::withdraw(double amount) {
    if (amount <= 0.0) throw InvalidAmountException("Withdrawal amount must be greater than zero.");
    if (status != AccountStatus::ACTIVE) throw AccountFrozenException("This account is not active.");
    if (balance - amount < -overdraftLimit) {
        throw InsufficientFundsException("Current account overdraft limit exceeded.");
    }

    balance -= amount;
    return record(Transaction(accountNumber + "-" + std::to_string(transactionCount + 1),
                              TransactionType::WITHDRAWAL, amount, accountNumber, "", balance));
}

std::string CurrentAccount::getAccountType() const { return "Current"; }

void CurrentAccount::applyMonthlyFee() {
    if (status == AccountStatus::ACTIVE && balance >= monthlyFee) {
        balance -= monthlyFee;
        record(Transaction(accountNumber + "-FEE", TransactionType::WITHDRAWAL,
                           monthlyFee, accountNumber, "", balance));
    }
}
