#include "SavingsAccount.hpp"

SavingsAccount::SavingsAccount(double interestRate)
    : SavingsAccount(0, interestRate)
{
}

SavingsAccount::SavingsAccount(double balance, double interestRate)
    : BankAccount(balance), interestRate(1 + interestRate)
{
}

void SavingsAccount::ApplyInterest()
{
    // treasury += balance * (interestRate - 1);

    double oldBalance = balance;
    balance *= interestRate;
    treasury += (balance - oldBalance);
}

double SavingsAccount::GetInterestRate() const
{
    return interestRate - 1;
}
