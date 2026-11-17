#include "StudentAccount.h"
#include "BankException.h"

StudentAccount::StudentAccount(const std::string& number, int ownerId, double openingBalance)
    : BankAccount(number, ownerId, openingBalance), studentId("STUDENT"),
      dailyWithdrawalLimit(500.0), withdrawnToday(0.0) {}

bool StudentAccount::withdraw(double amount) {
    if (amount <= 0.0) throw InvalidAmountException("Withdrawal amount must be greater than zero.");
    if (status != AccountStatus::ACTIVE) throw AccountFrozenException("This account is not active.");
    if (balance < amount || withdrawnToday + amount > dailyWithdrawalLimit) {
        throw InsufficientFundsException("Insufficient balance or daily withdrawal limit exceeded.");
    }

    balance -= amount;
    withdrawnToday += amount;
    return record(Transaction(accountNumber + "-" + std::to_string(transactionCount + 1),
                              TransactionType::WITHDRAWAL, amount, accountNumber, "", balance));
}

std::string StudentAccount::getAccountType() const { return "Student"; }
void StudentAccount::resetDailyLimit() { withdrawnToday = 0.0; }
