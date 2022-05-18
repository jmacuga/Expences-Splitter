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
        Person Janek(2, "Janek");
        Person Jula(3, "Julka");
        Trip trip("testtrip");
        double price = 11.5;
        std::shared_ptr<Transaction> trans = std::make_shared<CollectiveTransaction>(price, Milosz, food);
        assert((trans->get_money() == price));
        assert((trans->get_payer() == Milosz));
        trip.add_person(Milosz);
        trip.add_person(Janek);
        trip.add_person(Jula);
        trip.add_transaction(trans);
        assert((trip.get_ptransactions().size() == 1));
        assert((Milosz.get_balance() == price));
        std::vector<Person*> recievers{&Milosz, &Jula};
        std::shared_ptr<Transaction> spectrans = std::make_shared<SpecificTransaction>(30, Janek, alcohol, recievers);
        trip.add_transaction(spectrans);
        assert((trip.get_ptransactions().size() == 2));
        assert((trip.get_ptransactions()[1]->get_payer() == Janek));
        assert((Janek.get_balance() == 30));
    }

    std::cout << "\nEnd of logic tests\n";
    return 0;
}