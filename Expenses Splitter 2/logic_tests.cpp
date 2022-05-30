#include <iostream>
#include <cassert>
#include "Trip.h"
using namespace std;
template<typename T>
void compare_to_test(T actual, T expected, int test_n)
{
    if (actual != expected)
    {
        std::cout << "\ntest number: " << test_n << " failed";
        //std::cout << "\n     expected:" << expected << "\n    actual:" << actual;
    }
}

template<>
void compare_to_test(float actual, float expected, int test_n)
{
    if (!Transaction::fl_cmp(actual, expected))
    {
        std::cout << "\ntest number: " << test_n << " failed";
        //std::cout << "\n expected:" << expected << "\n    actual:" << actual;
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
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(1), 16.166667f), true, 11);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(2), -13.833333f), true, 12);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(0), -2.33333f), true, 13);
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
            trip.add_person(Julia);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(0), 6), true, 27);
            compare_to_test<bool>(Transaction::fl_cmp(trip.get_person_balance(1), -6), true, 28);
            std::map<std::pair<int, int>, float> transfers = trip.calc_transfers();
        }
        //transfers test1
        {
            Trip trip("testtrip");
            Person Milosz(1, "Milosz");
            Person Janek(2, "Janek");
            Person Jula(3, "Julka");
            trip.add_person(Milosz);
            trip.add_person(Janek);
            trip.add_person(Jula);
            std::shared_ptr<Transaction> trans = std::make_shared<CollectiveTransaction>(30.0f, 1, Person::Category::food);
            trip.add_transaction(trans);
            std::map<std::pair<int, int>, float> transfers1 = trip.calc_transfers();
            int sum = 0;
            compare_to_test<float>(transfers1.find({ 3, 1 })->second, 10.0f, 29 );
            compare_to_test<float>(transfers1.find({ 3, 1 })->second, 10.0f, 30 );

            std::vector<int> receivers{2, 3 };
            std::shared_ptr<Transaction> spectrans = std::make_shared<SpecificTransaction>(30.0f, 2, Person::Category::alcohol, receivers);
            trip.add_transaction(spectrans);
            std::map<std::pair<int, int>, float> transfers2 = trip.calc_transfers();
            compare_to_test<float>(transfers2.find({ 3, 1 })->second, 20.0f, 31);
            compare_to_test<float>(transfers2.find({ 3, 2 })->second, 5.0f, 32);
        }
        //transfers test2 - 4 people
        {
            Trip trip("testtrip");
            Person Milosz(1, "Milosz");
            Person Janek(2, "Janek");
            Person Jula(3, "Julka");
            Person Mati(4, "Mati");
            trip.add_person(Milosz);
            trip.add_person(Janek);
            trip.add_person(Jula);
            trip.add_person(Mati);
            trip.get_people() -> at(3).set_att(Person::Category::nicotine, true);
            std::shared_ptr<Transaction> trans1 = std::make_shared<CollectiveTransaction>(40.0f, 1, Person::Category::food);
            std::shared_ptr<Transaction> trans2 = std::make_shared<CollectiveTransaction>(20.0f, 2, Person::Category::nicotine);
            std::shared_ptr<Transaction> trans3 = std::make_shared<CollectiveTransaction>(80.0f, 1, Person::Category::alcohol);
            trip.add_transaction(trans1);
            trip.add_transaction(trans2);
            trip.add_transaction(trans3);
            std::map<std::pair<int, int>, float> transfers = trip.calc_transfers();
            compare_to_test<float>(transfers.find({ 2, 1 })->second, 10.0f, 33);
            compare_to_test<float>(transfers.find({ 3, 1 })->second, 30.0f, 34);
            compare_to_test<float>(transfers.find({ 4, 1 })->second, 50.0f, 35);
        }
        //transfers test 3
        {
            Trip trip("testtrip");
            Person Milosz(1, "Milosz");
            Person Janek(2, "Janek");
            Person Jula(3, "Julka");
            Person Mati(4, "Mati");
            trip.add_person(Milosz);
            trip.add_person(Janek);
            trip.add_person(Jula);
            trip.add_person(Mati);
            trip.get_people()->at(3).set_att(Person::Category::nicotine, true);
            std::shared_ptr<Transaction> trans1 = std::make_shared<CollectiveTransaction>(40.0f, 1, Person::Category::food);
            std::shared_ptr<Transaction> trans2 = std::make_shared<CollectiveTransaction>(40.0f, 2, Person::Category::nicotine);
            std::shared_ptr<Transaction> trans3 = std::make_shared<CollectiveTransaction>(80.0f, 1, Person::Category::alcohol);
            trip.add_transaction(trans1);
            trip.add_transaction(trans2);
            trip.add_transaction(trans3);
            std::map<std::pair<int, int>, float> transfers = trip.calc_transfers();
            compare_to_test<float>(transfers.find({ 3, 1 })->second, 30.0f, 36);
            compare_to_test<float>(transfers.find({ 4, 1 })->second, 60.0f, 37);
            compare_to_test<float>(transfers.find({ 4, 2 })->second, 10.0f, 38);
        }
        //transfers test 4
        {
            Trip trip("200_osob_w_kawalerce");
            Person Milosz(1, "Milosz");
            Person Janek(2, "Janek");
            Person Jula(3, "Julka");
            Person Mati(4, "Mati");
            Person Krzychu(5, "Mati");
            Person Mikolaj(6, "Mati");
            trip.add_person(Milosz);
            trip.add_person(Janek);
            trip.add_person(Jula);
            trip.add_person(Mati);
            trip.add_person(Krzychu);
            trip.add_person(Mikolaj);
            trip.get_people()->at(3).set_att(Person::Category::nicotine, true);
            trip.get_people()->at(4).set_att(Person::Category::nicotine, true);
            std::shared_ptr<Transaction> trans1 = std::make_shared<CollectiveTransaction>(55.0f, 1, Person::Category::food);
            std::shared_ptr<Transaction> trans2 = std::make_shared<CollectiveTransaction>(40.0f, 2, Person::Category::nicotine);
            std::shared_ptr<Transaction> trans3 = std::make_shared<CollectiveTransaction>(30.0f, 3, Person::Category::food);
            std::shared_ptr<Transaction> trans4 = std::make_shared<CollectiveTransaction>(100.0f, 4, Person::Category::alcohol);
            trip.add_transaction(trans1);
            trip.add_transaction(trans2);
            trip.add_transaction(trans3);
            trip.add_transaction(trans4);
            std::map<std::pair<int, int>, float> transfers = trip.calc_transfers();
            compare_to_test<float>(transfers.find({ 3, 2 })->second, 0.833f, 39);
            compare_to_test<float>(transfers.find({ 5, 1 })->second, 24.1667f, 40);
            compare_to_test<float>(transfers.find({ 5, 2 })->second, 8.333f, 41);
            compare_to_test<float>(transfers.find({ 5, 4 })->second, 18.333f, 42);
            compare_to_test<float>(transfers.find({ 6, 4 })->second, 30.833f, 43);
        }
    }
    std::cout << "\nEnd of logic tests\n";
    return 0;
}