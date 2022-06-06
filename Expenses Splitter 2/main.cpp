#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ui_actions.h"

Trip current_trip("curr_trip");

int main()
{
    std::cout << "\nExpenses Splitter\n";
    launch_app(current_trip);
    return 0;
}
