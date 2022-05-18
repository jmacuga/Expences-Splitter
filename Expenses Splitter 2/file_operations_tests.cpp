#include "Trip.h"
#include <iostream>
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
    Person jul(3, "Julka");
    std::vector<Person*> recievers{&pio, &jul};
    SpecificTransaction st(56.98, mil, other, recievers);
    tstr << "SPE\n1\n56.98\n4\n23\n";
    rstr << st.file_input();
    if (tstr.str() != rstr.str())
    {
        std::cout << "SpecificTransaction input test failed\n";
        std::cout << "Target: \n" << tstr.str() << "\nResult: \n" << rstr.str();
    }


    std::cout << "End of file operation tests.\n";
    return 0;
}