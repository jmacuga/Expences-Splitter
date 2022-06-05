#include <iostream>
#include "Person.h"
#include "Trip.h"
#include "ui_actions.h"

Trip current_trip("curr_trip");

int main()
{
    std::cout << "\nNazwa Aplikacji\n";
    launch_app(current_trip);
    return 0;
}
