#include <iostream>
#include <limits>
#include "ui_actions.h"
#include "ui_checks.cpp"


void launch_app()
{
    std::cout << "Choose options:\n";
    std::cout << "1. Add new trip.(Type '1')\n";
    std::cout << "2. Load trip information from database.(Type '2')\n";
    std::cout << "3. Exit.(Type '3')\n";
    int input = 0;
    while(!(std::cin >> input)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.  Try again (Type 1, 2 or 3): ";

    }
    if (check_init_action(input) == true)
        {
            if(input == 1)
                add_new_trip();
            else if(input == 2)
                load_history();
            else
                exit(0);
        }
    else
        {
        std::cout << "\nChoose proper option!\n";
        launch_app();
        }
}


void add_new_trip()
{
    std::cout << "\nNew trip:\n";
    //TODO
}


void load_history()
{
    std::cout << "\nLoad history:\n";
    //TODO
}