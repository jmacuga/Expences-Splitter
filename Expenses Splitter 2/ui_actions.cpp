#include <cstdio>
#include <ios>
#include <iostream>
#include <limits>
#include <fstream>
#include "ui_actions.h"
#include "ui_checks.h"
#include "Trip.h"

void launch_app(Trip& trip)
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
    if (check_init_action(input, 2))
        {
            switch (input)
            {
                case 1:
                    add_new_trip(trip);
                    break;
                case 2:
                    load_history(trip);
                    break;
                default:
                    exit(0);
                    break;
            }
        }
    else
        {
        std::cout << "\nChoose proper option!\n";
        launch_app(trip);
        }
}


void add_new_trip(Trip& trip)
{
    std::cout << "\nNew trip:\n";
    std::cout << "\nEnter the name of your trip:\n";
    std::string trip_name;
    std::cin >> trip_name;
    trip = Trip(trip_name);
    std::cin.clear();
    interface(trip);
}


void interface(Trip &trip)
{
    std::cout << "Choose option:\n";
    // Ja bym nie dał możliwości dawania tu transakcji, to dopiero po stworzeniu tripa
    // i przejsciu do takiego roboczego ekranu
    std::cout << "1. Add new participant. (Type '1')\n";
    std::cout << "2. Start adding new transactions. (Type '2')\n";
    std::cout << "3. Show people. (Type '3')\n";
    std::cout << "4. Show transaction history. (Type '4')\n";
    std::cout << "5. Show settlement. (Type '5')\n";
    std::cout << "6. Exit. (Type '6')\n";
    int input = 0;
    while(!(std::cin >> input)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.  Try again (Type 1 - 6): ";
    }
    if (check_init_action(input, 5))
        {
            switch (input)
            {
                case 1:
                    add_participant(trip);
                    break;
                case 2:
                    add_transactions(trip);
                    break;
                case 3:
                    trip.print_people(std::cout);
                    interface(trip);
                    break;
                case 4:
                    trip.print_trans(std::cout);
                    interface(trip);
                    break;
                case 5:
                    settle(trip);
                    break;
                default:
                    exit_app(trip);
                    break;
            }
        }
    else
        {
        std::cout << "\nChoose proper option!\n";
        add_new_trip(trip);
        }
}

void exit_app(Trip& trip)
{
    std::string saveline = trip.get_name() + "&./." + trip.get_name() + ".txt";
    std::ifstream trips;
    std::ofstream otrips;
    std::string line;
    bool file_new = true;
    trips.open("./trips.txt");
    getline(trips, line);
    while (line != "")
    {
        if (line == saveline)
            file_new = false;
        getline(trips, line);
    }
    trips.close();
    if (file_new)
    {
        otrips.open("./.trips.txt", std::ios::app);
        otrips << saveline << '\n';
        otrips.close();
    }
    otrips.open("./." + trip.get_name() + ".txt", std::ios::trunc);
    trip.save_to_file(otrips);
    otrips.close();
    exit(0);
}

void load_history(Trip &curr_trip)
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
        launch_app(curr_trip);
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
    int i = 0;std::ostream& print_people(std::ostream &os);
    for (const std::pair<std::string, std::string> &pa: tripsvect)
    {
        std::cout << i + 1 << ") " << pa.first << "\n";
        i += 1;
    }
    int input = 0;
    while (true)
    {
        try
        {std::cin >> input;}
        catch (...)
        {std::cin.clear();
         std::cout << "Input incorrect\n";
         continue;}
        if (input < 0 || input > i)
        {std::cout << "Input incorrect\n";
         continue;}
        break;
    }
    trpfile.open(tripsvect.at(input - 1).second);
    curr_trip = Trip(tripsvect.at(input - 1).first, trpfile);
    trpfile.close();
    std::cout << "Trip loaded succesfully!\n";
    interface(curr_trip);
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
    std::cout << "Do you want to change participant's attributes?\n";
    std::cout << "Preset is false for nicotine and true for everything else ";
    std::cout << "(food, alcohol, meat, gluten, dairy, other) [Y/N]\n";
    set_atts_action(trip_to_init, id);
    interface(trip_to_init);

}


void set_atts_action(Trip &trip_to_init, int id)
{
    std::string answer;
    std::cin >> answer;
    if (check_yes_no_input(answer))
    {
        if (is_positive(answer))
            set_attributes(trip_to_init, id);
        else
            interface(trip_to_init);
    }
    else
        {
            std::cout << "Wrong input. Answer has to be either 'Y' or 'N'\n";
            set_atts_action(trip_to_init, id);
        }
}

void set_attributes(Trip &trip_to_init, int person_id)
{
    std::cout << "What attribute do you want to change? Type number as an input\n";
    std::cout << trip_to_init.get_person(person_id - 1).print_atts();
    int input = 0;
    while (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.  Try again (Type nuber from 1 to 7): ";
    }
    Person::Category category = static_cast<Person::Category>(input - 1);
    trip_to_init.get_person(person_id - 1).set_att(category);
    std::cout << "AFTER CHANGE:\n" << trip_to_init.get_person(person_id - 1).print_atts();
    std::cout << "Do you want to change anything else? [Y/N] \n";
    std::string answer;
    std::cin >> answer;
    if (check_yes_no_input(answer))
        {
         if (is_positive(answer))
             set_attributes(trip_to_init, person_id);
       }
    else
        interface(trip_to_init);
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
    if (check_init_action(input, 2))
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

void settle(Trip& trip)
{
    std::cout << "Settle";
}