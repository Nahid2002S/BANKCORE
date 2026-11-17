#include "SavingsAccount.h"
#include "BankException.h"

SavingsAccount::SavingsAccount(const std::string& number, int ownerId, double openingBalance)
    : BankAccount(number, ownerId, openingBalance), interestRate(0.03), minimumBalance(500.0) {}

bool SavingsAccount::withdraw(double amount) {
    if (amount <= 0.0) throw InvalidAmountException("Withdrawal amount must be greater than zero.");
    if (status != AccountStatus::ACTIVE) throw AccountFrozenException("This account is not active.");
    if (balance - amount < minimumBalance) {
        throw InsufficientFundsException("Savings account minimum balance would be violated.");
    }

    balance -= amount;
    return record(Transaction(accountNumber + "-" + std::to_string(transactionCount + 1),
                              TransactionType::WITHDRAWAL, amount, accountNumber, "", balance));
}

std::string SavingsAccount::getAccountType() const { return "Savings"; }
double SavingsAccount::calculateInterest() const { return balance * interestRate; }
