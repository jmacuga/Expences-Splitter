#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include "Trip.h"

int main()
{
    // person file input test
    std::stringstream tstr;
    std::stringstream rstr;
    Person mil(1, "Miłosz");
    mil.set_att(Person::Category::other, false);
    tstr << "PER\n";
    tstr << "1 Miłosz\n";
    tstr << "1101110\n";
    rstr << mil.file_input();
    if (tstr.str() != rstr.str())
    {
        std::cout << "Person input test failed\n";
        std::cout << "Target: \n" << tstr.str() << "\nResult: \n" << rstr.str();
    }


    // CollectiveTransaction file input test
    tstr.str(std::string());
    rstr.str(std::string());
    Trip tsttrip("Test_trip");
    tsttrip.add_person(mil);
    CollectiveTransaction ct(40.5, 1, Person::Category::meat, 150);
    tstr << "COL\n150\n1\n40.5\n3\n";
    rstr << ct.file_input();
    if (tstr.str() != rstr.str())
    {
        std::cout << "CollectiveTransaction input test failed\n";
        std::cout << "Target: \n" << tstr.str() << "\nResult: \n" << rstr.str() << '\n';
    }


    // SpecificTransaction file input test
    tstr.str(std::string());
    rstr.str(std::string());
    Person pio(2, "Piotrek");
    pio.set_att(Person::Category::meat, false);
    Person jul(3, "Julka");
    jul.set_att(Person::Category::gluten, false);
    tsttrip.add_person(pio);
    tsttrip.add_person(jul);
    SpecificTransaction st(56.98, 1, Person::Category::other, {2, 3}, 150);
    tstr << "SPE\n150\n1\n56.98\n6\n23\n";
    rstr << st.file_input();
    if (tstr.str() != rstr.str())
    {
        std::cout << "SpecificTransaction input test failed\n";
        std::cout << "Target: \n" << tstr.str() << "\nResult: \n" << rstr.str();
    }


    // Save_to_file test 0
    tstr.str(std::string());
    rstr.str(std::string());

    tsttrip.add_transaction(std::make_shared<SpecificTransaction>(st));
    tsttrip.add_transaction(std::make_shared<CollectiveTransaction>(ct));


    std::ofstream sfile;
    sfile.open(".test_file.txt");
    tsttrip.save_to_file(sfile);
    sfile.close();

    std::ifstream ifile;
    ifile.open(".test_file.txt");
    std::string line;
    while (getline(ifile, line))
        rstr << line << '\n';
    ifile.close();

    ifile.open(".target_file.txt");
    line = "";
    while (getline(ifile, line))
        tstr << line << '\n';
    ifile.close();

    if (tstr.str() != rstr.str())
    {
        std::cout << "Save to file test failed\n";
        std::cout << "Target: \n" << tstr.str() << "\nResult: \n" << rstr.str();
    }
    std::remove(".test_file.txt");

    //save_to_file test 1
    tstr.str(std::string());
    rstr.str(std::string());

    Trip tsttrip1("Test_trip1");
    Person piotr(1, "Piotrek");
    Person wojtek(2, "Wojtek");
    SpecificTransaction st0(56.98, 1, Person::Category::other, {1, 2}, 150);
    CollectiveTransaction ct0(56.98, 1, Person::Category::other, 150);
    Person wiktoria(3, "Wiktoria");
    tsttrip1.add_person(piotr);
    tsttrip1.add_person(wojtek);
    tsttrip1.add_transaction(std::make_shared<SpecificTransaction>(st0));
    tsttrip1.add_transaction(std::make_shared<CollectiveTransaction>(ct0));
    tsttrip1.add_person(wiktoria);

    sfile.open(".test_file.txt");
    tsttrip1.save_to_file(sfile);
    sfile.close();

    ifile.open(".test_file.txt");
    line = "";
    while (getline(ifile, line))
        rstr << line << '\n';
    ifile.close();

    ifile.open(".target_file1.txt");
    line = "";
    while (getline(ifile, line))
        tstr << line << '\n';
    ifile.close();

    if (tstr.str() != rstr.str())
    {
        std::cout << "Save to file test 1 failed\n";
        std::cout << "Target: \n" << tstr.str() << "\nResult: \n" << rstr.str();
    }
    std::remove(".test_file.txt");


    // Load_from_file test 0
    Trip trptoload("Test_trip1");
    ifile.open(".target_file.txt");
    trptoload.load_from_file(ifile);
    ifile.close();
    assert(trptoload.get_person(0).get_name() == "Miłosz");
    assert(trptoload.get_person(1).get_name() == "Piotrek");
    assert(trptoload.get_person(2).get_name() == "Julka");
    assert(Transaction::fl_cmp(trptoload.get_person(0).get_balance(), 77.23));
    assert(Transaction::fl_cmp(trptoload.get_person(1).get_balance(), -28.49));
    assert(Transaction::fl_cmp(trptoload.get_person(2).get_balance(), -48.74));

    //load_from_file test 1
    Trip trptoload1("Test_trip2");
    ifile.open(".target_file1.txt");
    trptoload1.load_from_file(ifile);
    ifile.close();
    assert(trptoload1.get_person(0).get_name() == "Piotrek");
    assert(trptoload1.get_person(1).get_name() == "Wojtek");
    assert(trptoload1.get_person(2).get_name() == "Wiktoria");
    assert(Transaction::fl_cmp(trptoload1.get_person(0).get_balance(), 56.98));
    assert(Transaction::fl_cmp(trptoload1.get_person(1).get_balance(), -56.98));
    assert(Transaction::fl_cmp(trptoload1.get_person(2).get_balance(), 0));

    std::cout << "End of file operation tests.\n";
    return 0;
}

