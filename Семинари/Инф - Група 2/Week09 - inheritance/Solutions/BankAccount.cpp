#include "BankAccount.hpp"

int    BankAccount::idCounter = 0;
double BankAccount::treasury  = 0;

BankAccount::BankAccount()
    : id(idCounter++), balance(0)
{
}

BankAccount::BankAccount(double balance) : id(idCounter++), balance(balance)
{
    if (balance < 0)
        throw "J*b application";
    treasury += balance;
}

BankAccount::BankAccount(const BankAccount &other) : id(idCounter++), balance(other.balance)
{
    treasury += balance;
}

BankAccount &BankAccount::operator=(const BankAccount &other)
{
    balance = other.balance;
    treasury += balance;
    return *this;
}

BankAccount::~BankAccount()
{
    treasury -= balance;
}

int BankAccount::GetId() const
{
    return id;
}

double BankAccount::GetBalance() const
{
    return balance;
}

void BankAccount::Deposit(double money)
{
    if (money <= 0)
        return;

    balance += money;
    treasury += money;
}

double BankAccount::Withdraw(double money)
{
    if (money <= 0)
        return 0;

    if (money > balance)
        money = balance;

    balance -= money;
    treasury -= money;
    return money;
}

double BankAccount::GetTreasury()
{
    return treasury;
}

BankAccount operator+(BankAccount &left, BankAccount &right)
{
    double leftMoney  = left.Withdraw(left.GetBalance());
    double rightMoney = right.Withdraw(right.GetBalance());

    return BankAccount(leftMoney + rightMoney);
}

bool operator==(const BankAccount &left, const BankAccount &right)
{
    return left.GetId() == right.GetId();
}

std::ostream &operator<<(std::ostream &out, const BankAccount &account)
{
    out << "Account[" << account.GetId() << "] has " << account.GetBalance() << "$";
    return out;
}
