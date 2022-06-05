#include "Trip.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

int main()
{
    // person file input test
    std::stringstream tstr;
    std::stringstream rstr;
    Person mil(1, "Miłosz");
    mil.set_att(Person::Category::other, false);
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
    CollectiveTransaction ct(40.5, 1, Person::Category::meat);
    tstr << "COL\n1\n40.5\n3\n";
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
    // FIXME: jak sie dodaje drugą osobę to z jakiegoś powodu się
    // zeruje payer w collective transaction, zabawne
    tsttrip.add_person(pio);
    tsttrip.add_person(jul);
    std::vector<int> recievers{2, 3};
    SpecificTransaction st(56.98, 1, Person::Category::other, recievers);
    tstr << "SPE\n1\n56.98\n6\n23\n";
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

    // Load_from_fle test 0
    Trip trptoload("Test_trip1");
    ifile.open(".target_file.txt");
    trptoload.load_from_file(ifile);
    ifile.close();
    //assert(trptoload.get_people() -> size() == 3);
    assert(trptoload.get_person(0).get_name() == "Miłosz");
    assert(trptoload.get_person(1).get_name() == "Piotrek");
    assert(trptoload.get_person(2).get_name() == "Julka");
    assert(trptoload.get_trans_size() == 2);
    assert(Transaction::fl_cmp(trptoload.get_person(0).get_balance(), 77.23));
    assert(Transaction::fl_cmp(trptoload.get_person(1).get_balance(), -28.49));
    assert(Transaction::fl_cmp(trptoload.get_person(2).get_balance(), -48.74));

    std::cout << "End of file operation tests.\n";
    return 0;
}

