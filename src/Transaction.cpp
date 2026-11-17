#include "Transaction.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Transaction::Transaction()
    : type(TransactionType::DEPOSIT), amount(0.0), balanceAfter(0.0) {}

Transaction::Transaction(const std::string& id, TransactionType transactionType,
                         double transactionAmount, const std::string& source,
                         const std::string& destination, double afterBalance)
    : transactionId(id), sourceAccount(source), destinationAccount(destination),
      type(transactionType), amount(transactionAmount), balanceAfter(afterBalance) {
    const std::time_t now = std::time(nullptr);
    const std::tm* localTime = std::localtime(&now);
    char buffer[32] = {};

    if (localTime != nullptr) {
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    }
    dateTime = buffer;
}

std::string Transaction::getReceipt() const {
    std::ostringstream receipt;
    receipt << transactionId << " | " << static_cast<int>(type) << " | "
            << std::fixed << std::setprecision(2) << amount << " | " << dateTime
            << " | " << sourceAccount << " -> " << destinationAccount
            << " | Balance: " << balanceAfter;
    return receipt.str();
}

double Transaction::getAmount() const {
    return amount;
}
