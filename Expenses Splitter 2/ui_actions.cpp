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
    std::cout << "\nEnter the name of your trip:\n";
    std::string trip_name;
    std::cin >> trip_name;
    Trip trip(trip_name);
    initial_actions(trip);
}

void initial_actions(Trip &trip)
{
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


void add_participant(Trip &trip_to_init)
{
    std::cout << "\nAdd participant:\n";
    std::cout << "\nEnter the name of new participant:\n";
    std::string name;
    //FIXME ustawianie unikalnych id
    unsigned int id = trip_to_init.get_people_size() + 1;
    std::cin >> name;
    Person person_to_add(id, name);
    trip_to_init.add_person(person_to_add);
    initial_actions(trip_to_init);

}


void add_transactions(Trip &trip_to_init)
{
    std::cout << "\nAdd transactions:\n";
    std::cout << "Choose options:\n";
    std::cout << "1. Add collective transaction(all participants included).(Type '1')\n";
    std::cout << "2. Add specific transaction with limited number of participants.(Type '2')\n";
    int input = 0;
    while(!(std::cin >> input)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.  Try again (Type 1 or 2): ";

    }
    if (check_init_action_2_opt(input) == true)
        {
            if(input == 1)
                add_collective_transaction(trip_to_init);
            else
                add_specific_transaction(trip_to_init);
        }
    else
        {
        std::cout << "\nChoose proper option!\n";
        add_transactions(trip_to_init);
        }
}


void add_singular_transaction()
{
    std::cout << "\nAdd singular transactions:\n";
    //TODO
}

void add_collective_transaction(Trip &trip_to_init)
{
    std::cout << "\nAdd collective transaction:\n";
    //TODO category enum, searching payer by name (assuming that there are no 2 participants with the same name)
}

void add_specific_transaction(Trip &trip_to_init)
{
    std::cout << "\nAdd specific transaction:\n";
    //TODO
}