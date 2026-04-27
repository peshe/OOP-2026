#pragma once
#include "BankAccount.hpp"

class CheckingAccount : public BankAccount
{
public:
    CheckingAccount(double overdraftLimit);
    CheckingAccount(double balance, double overdraftLimit);

    double Withdraw(double money);

private:
    double overdraftLimit;
};
