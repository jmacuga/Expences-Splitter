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
    //test 2
    {
        Person Milosz(1, "Milosz");
        Trip trip("super trip");
        double price = 11.5;
        std::shared_ptr<Transaction> coll_trans = std::make_shared<Transaction>(price, Milosz, food);
        trip.add_person(Milosz);
        trip.add_transaction(coll_trans);
        assert((trip.get_ptransactions().size() == 1));
    }

    std::cout << "\nEnd of logic tests";
    return 0;
}