#include <iostream>
#include "Transactions.h"

int main()
{
    Person Milosz(1, "Milosz");
    double price = 11.5;
    categories c = food;
    CollectiveTransaction trans1(price, Milosz, food);
    std::cout << "\nEnd of logic tests";
    return 0;
}