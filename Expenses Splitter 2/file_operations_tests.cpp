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


    // Transaction file input test
    tstr.str(std::string());
    rstr.str(std::string());




    std::cout << "End of file operation tests.\n";
    return 0;
}