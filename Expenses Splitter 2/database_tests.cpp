#include "Database.h"
#include "Person.h"
#include <iostream>

int main()
// Tests for all funcionalities connected to the funcionalities of the database
{
    // tests init
    bool failed = false;

    // constructor test + basic operators
    Database<Person> dbp;
    Person mil(1, "Miłosz");
    mil.hd_true();
    dbp += mil;
    if (mil != dbp[0])
    {
        failed = true;
        std::cout << "Constructor failed" << "\n";
    }

    if (!failed)
    {
        std::cout << "Tests OK." << "\n";
    }

    return 0;
}