#include <iostream>
#include <cassert>
#include "Trip.h"
using namespace std;
template<typename T> void compare_to_test(T actual, T expected, int test_n)
{
    if (actual != expected)
    {
        std::cout << "\ntest number: " << test_n << " failed";
        //std::cout << "\n     expected:" << expected << "\n    actual:" << actual;
    }
}

int main()
{
    //test add_person();
    {
        Person Milosz(1, "Milosz");
        Trip trip("super trip");
        trip.add_person(Milosz);
        compare_to_test<size_t>(trip.get_people_size(), 1, 1);

        //test add_person() same person
        trip.add_person(Milosz);
        compare_to_test<size_t>(trip.get_people_size(), 1, 2);

    }
    //test Person::add_to_balance()
    {
        Person Milosz(1, "Milosz");
        Milosz.add_to_balace(10.0);
        compare_to_test<bool>(Transaction::fl_cmp(Milosz.get_balance(), 10.0), true, 3);
    }
    //test 2 Transactions::add_transaction()
    {
        //test case 1 - add collective transaction
        {
            Trip trip("testtrip");
            Person Milosz(1, "Milosz");
            Person Janek(2, "Janek");
            Person Jula(3, "Julka");
            trip.add_person(Milosz);
            trip.add_person(Janek);
            trip.add_person(Jula);
            float price = 11.50;
            std::shared_ptr<Transaction> trans = std::make_shared<CollectiveTransaction>(price, 1, Person::Category::food);
            compare_to_test<size_t>(Transaction::fl_cmp(trans->get_money(), price), true, 4);
            //FIXME przepraszam zepsułem jak zmieniałem koncepcje wektora
            //compare_to_test<Person>(trans->get_payer(), trip.get_people()->at(0), 5);
            trip.add_transaction(trans);
            compare_to_test<size_t>(trip.get_trans_size(), 1, 6);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(0), 2 * price / 3), true, 7);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(2), -price / 3), true, 8);
        }
        //test case 2 - add collective and specific transactions wi default person categories
        {
            Trip trip("testtrip");
            Person Milosz(1, "Milosz");
            Person Janek(2, "Janek");
            Person Jula(3, "Julka");
            trip.add_person(Milosz);
            trip.add_person(Janek);
            trip.add_person(Jula);
            float price = 11.50f;
            std::shared_ptr<Transaction> trans = std::make_shared<CollectiveTransaction>(price, 1, Person::Category::food);
            trip.add_transaction(trans);
            std::vector<int> receivers{1, 2, 3};
            std::shared_ptr<Transaction> spectrans = std::make_shared<SpecificTransaction>(30.0f, 2, Person::Category::alcohol, receivers);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(0),7.66667f),true,9);
            trip.add_transaction(spectrans);
            assert((trip.get_trans_size() == 2));
            //FIXME przepraszam zepsułem jak zmieniałem koncepcje wektora
            //compare_to_test(trip.get_trans_payer(1), trip.get_people()->at(1), 10);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(1), 16.166667f), true, 11);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(2), -13.833333f), true, 12);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(0), -2.33333f), true, 13);
            //FIXME przepraszam zepsułem jak zmieniałem koncepcje wektora
            //compare_to_test<Person>(*spectrans->get_included()[0], trip.get_people()->at(0), 14);
        }
        //test case 3 - make transaction with negative price
        {
            Trip trip("testtrip");
            Person Milosz(1, "Milosz");
            Person Janek(2, "Janek");
            Person Julia(3, "Julka");
            trip.add_person(Milosz);
            trip.add_person(Janek);
            trip.add_person(Julia);
            float price = -23.70f;
            try
            {
                std::shared_ptr<Transaction> trans = std::make_shared<CollectiveTransaction>(price, 1, Person::Category::dairy);
                std:cout << "\nException not thrown, test 15 failed";
            }
            catch (my_excetpions){};
        }
        //test case 4 - specify person category
        {
            //test person category compare
            {
                Person p(1, "Persososn");
                compare_to_test<bool>(p.category_compare(Person::Category::food), true, 16);
                compare_to_test<bool>(p.category_compare(Person::Category::alcohol), true, 17);
            }
            Trip trip("testtrip");
            Person Milosz(1, "Milosz");
            Person Janek(2, "Janek");
            Person Julia(3, "Julia");
            Julia.set_att(Person::Category::nicotine, true);
            Julia.set_att(Person::Category::food, false);
            Milosz.set_att(Person::Category::nicotine, false);
            Milosz.set_att(Person::Category::food, false);
            Janek.set_att(Person::Category::nicotine, true);
            Janek.set_att(Person::Category::food, true);
            trip.add_person(Milosz);
            trip.add_person(Janek);
            trip.add_person(Julia);
            float price = 4.20f;
            std::shared_ptr<Transaction> trans = std::make_shared<CollectiveTransaction>(price, 1, Person::Category::food);
            trip.add_transaction(trans);
            compare_to_test<bool>(Julia.category_compare(Person::Category::alcohol), true, 18);
            compare_to_test<bool>(Julia.category_compare(Person::Category::food), false, 19);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(0), 4.20000f), true, 21);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(1), -4.20000f), true, 22);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(2), 0.0f), true, 20);
            Julia.set_att(Person::Category::food, true);
            compare_to_test<bool>(Julia.category_compare(Person::Category::food), true, 23);
        }

        {
            Trip trip("testtrip");
            Person Milosz(1, "Milosz");
            Person Janek(2, "Janek");
            Person Julia(3, "Julia");
            trip.add_person(Milosz);
            trip.add_person(Janek);
            float price = 12.0f;
            std::shared_ptr<Transaction> trans = std::make_shared<CollectiveTransaction>(price, 1, Person::Category::food);
            trip.add_transaction(trans);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(0), 6), true, 24);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(1), -6), true, 25);
            //FIXME przepraszam zepsułem jak zmieniałem koncepcje wektora
            //compare_to_test<Person>(trip.get_trans_payer(0), trip.get_people()->at(0), 26);
            trip.add_person(Julia);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(0), 6), true, 27);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(1), -6), true, 28);
            //kraksa
            //compare_to_test<Person>(trip.get_trans_payer(0), trip.get_people()->at(0), 29);
        }

    }
    std::cout << "\nEnd of logic tests\n";
    return 0;
}