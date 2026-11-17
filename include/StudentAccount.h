#ifndef STUDENT_ACCOUNT_H
#define STUDENT_ACCOUNT_H

#include "BankAccount.h"

class StudentAccount : public BankAccount {
private:
    std::string studentId;
    double dailyWithdrawalLimit;
    double withdrawnToday;

public:
    StudentAccount(const std::string& number, int ownerId, double openingBalance);
    bool withdraw(double amount) override;
    std::string getAccountType() const override;
    void resetDailyLimit();
};

#endif // STUDENT_ACCOUNT_H
