#include <iostream>
#include <cassert>
#include "Trip.h"

int main()
{
    //test 1 add_person();
    {
        Person Milosz(1, "Milosz");
        Trip trip("super trip");
        trip.add_person(Milosz);
        assert((trip.get_people().size() == 1));
        //test add_person() same person
        trip.add_person(Milosz);
        assert((trip.get_people().size() == 1));

    }
    //test Person::add_to_balance()
    {
        Person Milosz(1, "Milosz");
        Milosz.add_to_balace(10);
        assert((Milosz.get_balance() == 10));
    }
    //test 2 TTransactions::add_transaction()
    {
        Person Milosz(1, "Milosz");
        Person Janek(2, "Milosz");
        Trip trip("testtrip");
        double price = 11.5;
        std::shared_ptr<Transaction> trans = std::make_shared<Transaction>(price, Milosz, food);
        assert((trans->get_money() == price));
        assert((trans->get_payer() == Milosz));
        trip.add_person(Milosz);
        trip.add_person(Janek);
        trip.add_transaction(trans);
        assert((trip.get_ptransactions().size() == 1));
        assert((Milosz.get_balance() == price));
    }

    std::cout << "\nEnd of logic tests";
    return 0;
}