# BANKCORE — Bank Account Manager

A C++17, terminal-based banking management project developed for Object-Oriented Programming II. The design follows the BANKCORE UML v7 and uses fixed-size arrays rather than `std::vector`.

## Project structure

```text
BANKCORE/
├── include/                 # Class declarations and shared types
│   ├── BankCore.h           # Convenience header for the complete project API
│   ├── BankSystemTypes.h
│   ├── BankException.h
│   ├── Transaction.h
│   ├── Customer.h
│   ├── BankAccount.h
│   ├── SavingsAccount.h
│   ├── CurrentAccount.h
│   ├── StudentAccount.h
│   ├── Authentication.h
│   ├── FileManager.h
│   └── BankManager.h
├── src/                     # Class implementations and application entry point
│   ├── Transaction.cpp
│   ├── Customer.cpp
│   ├── BankAccount.cpp
│   ├── SavingsAccount.cpp
│   ├── CurrentAccount.cpp
│   ├── StudentAccount.cpp
│   ├── Authentication.cpp
│   ├── FileManager.cpp
│   ├── BankManager.cpp
│   └── main.cpp
├── data/                    # Runtime data files are created here
├── README.md
└── .gitignore
```

## Requirements

- GCC with C++17 support (GCC 8+ recommended; a current MSYS2 UCRT64 GCC is suitable)
- Windows, Linux, or macOS terminal

## Build on Windows (PowerShell)

Run from the project root:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o BankCore.exe
.\BankCore.exe
```

## Build on Linux / macOS

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o BankCore
./BankCore
```

## Demo administrator login

- Username: `admin`
- Password: `admin123`

This is a classroom demonstration credential only. Passwords are not securely hashed in this initial version.

## Initial features

- Administrator login
- Customer registration and lookup
- Savings, Current, and Student account creation
- Deposits, withdrawals, and transfers
- Customer/account listing and daily summary report
- Abstract `BankAccount` base class and derived account classes
- Virtual functions and runtime polymorphism
- Custom exception hierarchy
- Fixed-size arrays and explicit capacity limits
- Initial customer/account file-writing and customer-file loading

## Known limitations — important

This is an initial project milestone, not a completed banking application.

- Customer records are loaded from `data/customers.txt`.
- Account records can be saved, but `loadAccounts()` currently counts saved records; it does **not** reconstruct derived account objects.
- Customer-to-account relationships are not restored after restarting because the current customer file format does not save those account-number links.
- Transaction objects are kept in each account's in-memory fixed array, but central transaction-file integration is not yet connected to every banking operation.
- The StudentAccount currently uses a placeholder student ID (`STUDENT`).
- Authentication uses a demonstration plain-text password.
- Transfer rollback and persistence should receive further testing before final submission.

## Suggested next milestones

1. Implement full account deserialization using the saved account type and restore derived account objects.
2. Persist and restore customer-account relationships, account status, and account-number counters.
3. Connect all successful deposits, withdrawals, and both sides of transfers to the transaction log.
4. Improve transaction rollback so a failed transfer leaves both balances and transaction histories unchanged.
5. Add stronger input validation and test invalid files, malformed records, full arrays, and all account types.
6. Test saving, closing, and reopening the application to verify persistence.

## OOP concepts demonstrated

- **Encapsulation:** class data is private or protected and accessed through methods.
- **Inheritance:** SavingsAccount, CurrentAccount, and StudentAccount derive from BankAccount.
- **Abstraction:** BankAccount is abstract and defines pure virtual operations.
- **Polymorphism:** BankAccount pointers call overridden derived-class functions.
- **Composition/ownership:** BankManager owns dynamically allocated account objects and deletes them in its destructor.
