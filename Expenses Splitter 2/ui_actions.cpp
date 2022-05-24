#include <iostream>
#include <limits>
#include <fstream>
#include "ui_actions.h"
#include "ui_checks.h"
#include "Trip.h"


void launch_app()
{
    std::cout << "Choose options:\n";
    std::cout << "1. Add new trip. (Type '1')\n";
    std::cout << "2. Load trip. (Type '2')\n";
    std::cout << "3. Exit. (Type '3')\n";
    int input = 0;
    while(!(std::cin >> input)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.  Try again (Type 1, 2 or 3): ";

    }
    if (check_init_action(input) == true)
        {
            switch (input)
            {
                case 1:
                    add_new_trip();
                    break;
                case 2:
                    load_history();
                    break;
                default:
                    exit(0);
                    break;
            }
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
    std::string trip_name;
    Trip trip(trip_name);
    std::cout << "Choose options:\n";
    // Ja bym nie dał możliwości dawania tu transakcji, to dopiero po stworzeniu tripa
    // i przejsciu do takiego roboczego ekranu
    std::cout << "1. Add new participant.(Type '1')\n";
    std::cout << "2. Start adding new transactions.(Type '2')\n";
    std::cout << "3. Exit.(Type '3')\n";
    int input = 0;
    while(!(std::cin >> input)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.  Try again (Type 1, 2 or 3): ";

    }
    if (check_init_action(input) == true)
        {
            switch (input)
            {
                case 1:
                    add_participants();
                    break;
                case 2:
                    add_transactions();
                    break;
                default:
                    exit(0);
                    break;
            }
        }
    else
        {
        std::cout << "\nChoose proper option!\n";
        add_new_trip();
        }
}


void load_history()
{
    std::cout << "\nChoose trip:\n";
    std::ifstream trpfile;
    std::string line;
    std::pair<std::string, std::string> trip_inf;
    std::vector<std::pair<std::string, std::string>> tripsvect;
    trpfile.open("./.trips.txt");
    getline(trpfile, line);
    // Shows info if there are no trips saved
    if (line == "")
    {
        std::cout << "No trips found :(\n\n";
        launch_app();
    }
    else
    // Loading info about existing trips into vector
        while (line != "")
        {
            bool amp = false;
            for (const char &c: line)
                if (!amp)
                {
                    if (c == '&')
                    {
                        amp = true;
                        continue;
                    }
                    trip_inf.first += c;
                }
                else
                    trip_inf.second += c;
                tripsvect.push_back(trip_inf);
                trip_inf.first = std::string();
                trip_inf.second = std::string();
                getline(trpfile, line);
        }
    trpfile.close();
    int i = 0;
    for (const std::pair<std::string, std::string> &pa: tripsvect)
    {
        std::cout << i + 1 << ") " << pa.first << "\n";
        i += 1;
    }

}


void add_participants()
{
    std::cout << "\nAdd participants:\n";
    //TODO
}

// naaaahhhhhh
void add_transactions()
{
    std::cout << "\nAdd transactions:\n";
    //TODO
}


void add_singular_transaction()
{
    std::cout << "\nAdd singular transactions:\n";
    //TODO
}

void trip_interface(Trip trp)
{
    //TODO tu się będzie dodawało transakcjje i działo się będzie główne działanie apki
}