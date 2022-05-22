#include <iostream>
#include "ui_actions.h"
#include "ui_checks.cpp"


void launch_app()
{
    std::cout << "Choose options:\n";
    std::cout << "1. Add new trip.(Type '1')\n";
    std::cout << "2. Load trip information from database.(Type '2')\n";
    int output;
    std::cin >> output;
    if (check_init_action(output) == true)
        {
            if(output == 1)
                add_new_trip();
            else
                load_history();
        }
    else
        launch_app();
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