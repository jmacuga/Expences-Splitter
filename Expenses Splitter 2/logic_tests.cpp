#include <iostream>
#include <cassert>
#include "Trip.h"

int main()
{
    //test add_person();
    {
        Person Milosz(1, "Milosz");
        Trip trip("super trip");
        trip.add_person(Milosz);
        assert((trip.get_people() -> size() == 1));
        //test add_person() same person
        trip.add_person(Milosz);
        assert((trip.get_people() -> size() == 1));

    }
    //test Person::add_to_balance()
    {
        Person Milosz(1, "Milosz");
        Milosz.add_to_balace(10.0);
        assert((Milosz.get_balance() == 10.0));
    }
    //test 2 Transactions::add_transaction()
    {
        //test case 1
        {
            Trip trip("testtrip");
            Person Milosz(1, "Milosz");
            Person Janek(2, "Janek");
            Person Jula(3, "Julka");
            trip.add_person(Milosz);
            trip.add_person(Janek);
            trip.add_person(Jula);
            float price = 11.50;
            std::shared_ptr<Transaction> trans = std::make_shared<CollectiveTransaction>(price, Milosz, Person::Category::food);
            assert((trans->get_money() == price));
            assert((trans->get_payer() == Milosz));
            trip.add_transaction(trans);
            assert((trip.get_ptransactions().size() == 1));
            assert((Milosz.get_balance(), 2 * price / 3));
        }
        //test case 2
        {
            Trip trip("testtrip");
            Person Milosz(1, "Milosz");
            Person Janek(2, "Janek");
            Person Jula(3, "Julka");
            trip.add_person(Milosz);
            trip.add_person(Janek);
            trip.add_person(Jula);
            float price = 11.50;
            std::shared_ptr<Transaction> trans = std::make_shared<CollectiveTransaction>(price, Milosz, Person::Category::food);
            trip.add_transaction(trans);
            std::vector<Person*> receivers{ &Milosz, &Jula };
            std::shared_ptr<Transaction> spectrans = std::make_shared<SpecificTransaction>(30, Janek, Person::Category::alcohol, receivers);
            assert(Transaction::fl_cmp(Milosz.get_balance(),7.66667));
            trip.add_transaction(spectrans);
            assert((trip.get_ptransactions().size() == 2));
            assert((trip.get_ptransactions()[1]->get_payer() == Janek));
            assert(Transaction::fl_cmp(Janek.get_balance(),20));
            assert(Transaction::fl_cmp(Jula.get_balance(),-10));
            assert(Transaction::fl_cmp(Milosz.get_balance(),-2.33334));
            assert((*spectrans->get_included()[0] == Milosz));
        }
        //test case 3 - split between included people
        {

        }
    }
    std::cout << "\nEnd of logic tests\n";
    return 0;
}