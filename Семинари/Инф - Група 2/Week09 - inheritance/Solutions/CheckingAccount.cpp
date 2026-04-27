#include "CheckingAccount.hpp"

CheckingAccount::CheckingAccount(double overdraftLimit)
    : CheckingAccount(0, overdraftLimit)
{
}

CheckingAccount::CheckingAccount(double balance, double overdraftLimit)
    : BankAccount(balance), overdraftLimit(overdraftLimit)
{
    if (overdraftLimit < 0)
        throw "Negative overdraft...?";
}

double CheckingAccount::Withdraw(double money)
{
    if (money <= 0)
        return 0;

    if (money > balance + overdraftLimit)
        money = balance + overdraftLimit;

    balance -= money;
    treasury -= money;
    return money;
}
