#ifndef BANK_SYSTEM_TYPES_H
#define BANK_SYSTEM_TYPES_H

enum class AccountStatus { ACTIVE, FROZEN, CLOSED };
enum class TransactionType { DEPOSIT, WITHDRAWAL, TRANSFER_IN, TRANSFER_OUT };
enum class UserRole { ADMIN, CUSTOMER };

#endif // BANK_SYSTEM_TYPES_H
