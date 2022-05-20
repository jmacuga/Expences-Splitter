#include <iostream>
#include <cassert>
#include "Trip.h"

float const EPS = 0.00001;
bool are_equal(float a, float b)
{
    return abs(a - b) < EPS;
};
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
            std::shared_ptr<Transaction> trans = std::make_shared<CollectiveTransaction>(price, Milosz, food);
            assert((trans->get_money() == price));
            assert((trans->get_payer() == Milosz));
            trip.add_transaction(trans);
            assert((trip.get_ptransactions().size() == 1));
            assert(are_equal(Milosz.get_balance(), 2 * price / 3));
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
            std::shared_ptr<Transaction> trans = std::make_shared<CollectiveTransaction>(price, Milosz, food);
            trip.add_transaction(trans);
            std::vector<Person*> receivers{ &Milosz, &Jula };
            std::shared_ptr<Transaction> spectrans = std::make_shared<SpecificTransaction>(30, Janek, alcohol, receivers);
            assert(are_equal(Milosz.get_balance(),7.66667));
            trip.add_transaction(spectrans);
            assert((trip.get_ptransactions().size() == 2));
            assert((trip.get_ptransactions()[1]->get_payer() == Janek));
            assert(are_equal(Janek.get_balance(),20));
            assert(are_equal(Jula.get_balance(),-10));
            assert(are_equal(Milosz.get_balance(),-2.33334));
            assert((*spectrans->get_included()[0] == Milosz));
        }
        //test case 3 - split between included people
        {

        }
    }
    std::cout << "\nEnd of logic tests\n";
    return 0;
}