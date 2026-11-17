#ifndef BANK_EXCEPTION_H
#define BANK_EXCEPTION_H

#include <stdexcept>
#include <string>

class BankException : public std::exception {
private:
    std::string message;

public:
    explicit BankException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InsufficientFundsException : public BankException {
public:
    explicit InsufficientFundsException(const std::string& msg) : BankException(msg) {}
};

class AccountFrozenException : public BankException {
public:
    explicit AccountFrozenException(const std::string& msg) : BankException(msg) {}
};

class InvalidAmountException : public BankException {
public:
    explicit InvalidAmountException(const std::string& msg) : BankException(msg) {}
};

class AccountNotFoundException : public BankException {
public:
    explicit AccountNotFoundException(const std::string& msg) : BankException(msg) {}
};

class FileException : public BankException {
public:
    explicit FileException(const std::string& msg) : BankException(msg) {}
};

#endif // BANK_EXCEPTION_H
