#include "BankCore.h"
#include <iostream>
#include <limits>
#include <string>

namespace {
void clearInputLine() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool readNumber(const std::string& prompt, double& value) {
    std::cout << prompt;
    if (std::cin >> value) {
        clearInputLine();
        return true;
    }
    clearInputLine();
    std::cout << "Invalid numeric input. Please try again.\n";
    return false;
}

bool readInteger(const std::string& prompt, int& value) {
    std::cout << prompt;
    if (std::cin >> value) {
        clearInputLine();
        return true;
    }
    clearInputLine();
    std::cout << "Invalid integer input. Please try again.\n";
    return false;
}
}

int main() {
    try {
        BankManager bank;
        Authentication admin;

        std::cout << "============================================\n"
                  << "               BANKCORE TERMINAL            \n"
                  << "          BANK ACCOUNT MANAGEMENT SYSTEM    \n"
                  << "============================================\n"
                  << "Demo login: admin / admin123\n";

        std::string username;
        std::string password;
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        if (!admin.login(username, password)) {
            std::cout << "Login failed.\n";
            return 0;
        }
        clearInputLine();

        int choice = -1;
        do {
            std::cout << "\n--------------- MAIN MENU -----------------\n"
                      << "1. Register customer\n2. Open account\n3. Deposit\n4. Withdraw\n"
                      << "5. Transfer\n6. Find customer\n7. List customers\n"
                      << "8. List accounts\n9. Daily report\n0. Exit\nSelect: ";

            if (!(std::cin >> choice)) {
                clearInputLine();
                std::cout << "Please enter a valid menu number.\n";
                continue;
            }
            clearInputLine();

            try {
                if (choice == 1) {
                    std::string name, phone, email, address;
                    std::cout << "Full name: "; std::getline(std::cin, name);
                    std::cout << "Phone: "; std::getline(std::cin, phone);
                    std::cout << "Email: "; std::getline(std::cin, email);
                    std::cout << "Address: "; std::getline(std::cin, address);

                    Customer* customer = bank.registerCustomer(name, phone, email, address);
                    if (customer != nullptr) {
                        std::cout << "Customer created. ID: " << customer->getCustomerId() << '\n';
                    } else {
                        std::cout << "Customer capacity full.\n";
                    }
                } else if (choice == 2) {
                    int customerId, accountType;
                    double openingBalance;
                    if (!readInteger("Customer ID: ", customerId) ||
                        !readInteger("Type (1 Savings, 2 Current, 3 Student): ", accountType) ||
                        !readNumber("Opening balance: ", openingBalance)) continue;

                    std::cout << (bank.openAccount(customerId, accountType, openingBalance)
                                  ? "Account opened.\n" : "Could not open account.\n");
                } else if (choice == 3 || choice == 4) {
                    std::string accountNumber;
                    double amount;
                    std::cout << "Account number: "; std::getline(std::cin, accountNumber);
                    if (!readNumber("Amount: ", amount)) continue;

                    const bool success = (choice == 3)
                        ? bank.deposit(accountNumber, amount)
                        : bank.withdraw(accountNumber, amount);
                    std::cout << (success ? "Transaction successful.\n" : "Transaction rejected.\n");
                } else if (choice == 5) {
                    std::string fromAccount, toAccount;
                    double amount;
                    std::cout << "From account: "; std::getline(std::cin, fromAccount);
                    std::cout << "To account: "; std::getline(std::cin, toAccount);
                    if (!readNumber("Amount: ", amount)) continue;

                    std::cout << (bank.transfer(fromAccount, toAccount, amount)
                                  ? "Transfer completed.\n" : "Transfer failed.\n");
                } else if (choice == 6) {
                    int customerId;
                    if (!readInteger("Customer ID: ", customerId)) continue;
                    Customer* customer = bank.findCustomer(customerId);
                    if (customer != nullptr) customer->viewAccounts();
                    else std::cout << "Customer not found.\n";
                } else if (choice == 7) {
                    bank.listCustomers();
                } else if (choice == 8) {
                    bank.listAccounts();
                } else if (choice == 9) {
                    bank.generateDailyReport();
                } else if (choice == 0) {
                    std::cout << "Thank you for using BANKCORE.\n";
                } else {
                    std::cout << "Invalid selection.\n";
                }
            } catch (const BankException& error) {
                std::cout << "BANKCORE ERROR: " << error.what() << '\n';
            } catch (const std::exception& error) {
                std::cout << "SYSTEM ERROR: " << error.what() << '\n';
            }
        } while (choice != 0);
    } catch (const std::exception& error) {
        std::cerr << "FATAL ERROR: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
