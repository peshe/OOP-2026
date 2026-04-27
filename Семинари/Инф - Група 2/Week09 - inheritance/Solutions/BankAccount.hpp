#pragma once
#include <iostream>

class BankAccount
{
public:
    BankAccount();
    BankAccount(double balance);
    BankAccount(const BankAccount &other);
    BankAccount &operator=(const BankAccount &other);
    ~BankAccount();

    int    GetId() const;
    double GetBalance() const;

    void   Deposit(double money);
    double Withdraw(double money);

    static double GetTreasury();

protected:
    double        balance;
    static double treasury;

private:
    static int idCounter;
    int        id;
};

BankAccount operator+(BankAccount &left, BankAccount &right);

bool operator==(const BankAccount &left, const BankAccount &right);

std::ostream &operator<<(std::ostream &out, const BankAccount &account);
