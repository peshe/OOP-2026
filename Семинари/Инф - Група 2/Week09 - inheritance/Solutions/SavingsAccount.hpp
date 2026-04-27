#pragma once
#include "BankAccount.hpp"

class SavingsAccount : public BankAccount
{
public:
    SavingsAccount(double interestRate);
    SavingsAccount(double balance, double interestRate);

    void   ApplyInterest();
    double GetInterestRate() const;

private:
    double interestRate;
};
