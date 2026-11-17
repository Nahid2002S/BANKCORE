#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class FileManager;

class Customer {
private:
    int customerId;
    std::string fullName;
    std::string phone;
    std::string email;
    std::string address;
    std::string accountNumbers[5];
    int accountCount;

public:
    Customer();
    Customer(int id, const std::string& name, const std::string& phone,
             const std::string& email, const std::string& address);

    int getCustomerId() const;
    std::string getName() const;
    int getAccountCount() const;
    std::string getAccountNumber(int index) const;
    bool addAccountNumber(const std::string& number);
    bool removeAccountNumber(const std::string& number);
    void viewAccounts() const;

    friend class FileManager;
};

#endif // CUSTOMER_H
