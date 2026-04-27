#include <iostream>
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"

int main()
{
    BankAccount b1(150);
    BankAccount b2(2000);

    std::cout << b1 << '\n';
    std::cout << b2 << '\n';

    BankAccount b3 = b1 + b2;

    std::cout << b1 << '\n';
    std::cout << b2 << '\n';
    std::cout << b3 << '\n'
              << '\n';

    SavingsAccount s1(700, 0.2);

    std::cout << s1 << '\n';
    std::cout << "Applying Interest...\n";

    s1.ApplyInterest();

    std::cout << s1 << '\n'
              << '\n';

    std::cout << "Treasury: $" << BankAccount::GetTreasury() << "\n\n";

    CheckingAccount c1(1000, 2000);

    std::cout << c1 << '\n';

    double cash1 = c1.Withdraw(900);
    std::cout << "Wanted: 900$\tWithdrew: " << cash1 << "$\n";
    std::cout << c1 << '\n';

    double cash2 = c1.Withdraw(900);
    std::cout << "Wanted: 900$\tWithdrew: " << cash2 << "$\n";
    std::cout << c1 << '\n';

    double cash3 = c1.Withdraw(900);
    std::cout << "Wanted: 900$\tWithdrew: " << cash3 << "$\n";
    std::cout << c1 << '\n';

    double cash4 = c1.Withdraw(900);
    std::cout << "Wanted: 900$\tWithdrew: " << cash4 << "$\n";
    std::cout << c1 << '\n';
}
