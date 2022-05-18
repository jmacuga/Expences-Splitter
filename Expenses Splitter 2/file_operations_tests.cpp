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
    //Person pio(2, "Piotrek");
    //Person jul(3, "Julka");
    mil.set_heavy_drinker(true);
    //pio.set_meat(false);
    //jul.set_balance(30.5);
    tstr << "1 Miłosz\n";
    tstr << mil.get_balance() << '\n';
    tstr << "111110\n";
    rstr << mil.file_input();
    if (tstr.str() != rstr.str())
    {
        std::cout << "Person input test failed\n";
        std::cout << "Target: \n" << tstr.str() << "\nResult: \n" << rstr.str();
    }


    // CollectiveTransaction file input test
    tstr.str(std::string());
    rstr.str(std::string());
    CollectiveTransaction ct(40.5, mil, meat);
    tstr << "COL\n1\n40.5\n3\n";
    rstr << ct.file_input();
    if (tstr.str() != rstr.str())
    {
        std::cout << "CollectiveTransaction input test failed\n";
        std::cout << "Target: \n" << tstr.str() << "\nResult: \n" << rstr.str();
    }


    // SpecificTransaction file input test
    tstr.str(std::string());
    rstr.str(std::string());
    Person pio(2, "Piotrek");
    pio.set_meat(false);
    Person jul(3, "Julka");
    jul.set_gluten(false);
    std::vector<Person*> recievers{&pio, &jul};
    SpecificTransaction st(56.98, mil, other, recievers);
    tstr << "SPE\n1\n56.98\n4\n23\n";
    rstr << st.file_input();
    if (tstr.str() != rstr.str())
    {
        std::cout << "SpecificTransaction input test failed\n";
        std::cout << "Target: \n" << tstr.str() << "\nResult: \n" << rstr.str();
    }


    // Save_to_file test
    tstr.str(std::string());
    rstr.str(std::string());


    Trip tsttrip("Test_trip");
    tsttrip.add_person(mil);
    tsttrip.add_person(pio);
    tsttrip.add_person(jul);
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

    std::cout << "End of file operation tests.\n";
    return 0;
}