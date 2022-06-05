#include <cstdio>
#include <ios>
#include <iostream>
#include <limits>
#include <fstream>
#include <memory>
#include "Person.h"
#include "Transactions.h"
#include <string>
#include "ui_actions.h"
#include "ui_checks.h"
#include "Trip.h"

void launch_app(Trip& trip)
{
    std::cout << "Choose options:\n";
    std::cout << "1. Add new trip. (Type '1')\n";
    std::cout << "2. Load trip. (Type '2')\n";
    std::cout << "3. Exit. (Type '3')\n";
    int input = numerical_input("Invalid input.  Try again (Type 1, 2 or 3): ", 1, 3);
    system("CLS");
    switch (input)
    {
        case 1:
            add_new_trip(trip);
            break;
        case 2:
            load_history(trip);
        default:
            exit(0);
            break;
    }
    if (check_init_action(input, 3))
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
    std::cin.ignore();
    std::getline(std::cin, trip_name);
    trip = Trip(trip_name);
    std::cin.clear();
    interface(trip);
}


void interface(Trip &trip)
{
    system("CLS");
    std::cout << "Choose option:\n";
    std::cout << "1. Add new participant. (Type '1')\n";
    std::cout << "2. Start adding new transactions. (Type '2')\n";
    std::cout << "3. Show people. (Type '3')\n";
    std::cout << "4. Show transaction history. (Type '4')\n";
    std::cout << "5. Show settlement. (Type '5')\n";
    std::cout << "6. Exit. (Type '6')\n";
    int input = numerical_input("Invalid input.  Try again (Type number from 1 to 6): ", 1, 6);
    system("CLS");
    switch (input)
    {
        case 1:
            add_participant(trip);
            break;
        case 2:
            add_transactions(trip);
            break;
        case 3:
            show_people(trip);
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

void exit_app(Trip& trip)
{
    std::string saveline = trip.get_name() + "&./." + trip.get_name() + ".txt";
    std::ifstream trips;
    std::ofstream otrips;
    std::string line;
    bool file_new = true;
    trips.open("./.trips.txt");
    getline(trips, line);
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
        std::cout << i++ + 1 << ") " << pa.first << "\n";
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
    std::cout << "Do you want to change participant's attributes? [Y/N]\n";
    std::cout << trip_to_init.get_person(id - 1).print_atts();
    set_atts_action(trip_to_init, id);
    interface(trip_to_init);
}

void show_people(Trip& trip)
{
    trip.print_people(std::cout);
    std::cout << "Press Enter to continue...";
    std::cin.ignore(10, '\n');
    std::cin.get();
    interface(trip);
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

template<typename T>
T numerical_input(std::string message, T min, T max)
{
    std::string input;
    T input_val = 0;
    while (true)
    {
        try
        {
            std::cin >> input;
            input_val = std::stoi(input);
            if (input_val >= min && input_val <= max)
                break;
        }
        catch(...) {}
        std::cout << message;
    }
    return input_val;
}

template<>
float numerical_input(std::string message, float min, float max)
{
    std::string input;
    float input_val = 0;
    while (true)
    {
        try
        {
            std::cin >> input;
            input_val = std::stof(input);
            if (input_val >= min && input_val <= max)
                break;
        }
        catch (...) {}
        std::cout << message;
    }
    return input_val;
}

void set_attributes(Trip &trip_to_init, int person_id)
{
    system("CLS");
    std::cout << "What attribute do you want to change? Type number as an input\n";
    std::cout << trip_to_init.get_person(person_id - 1).print_atts();
    int input = numerical_input("Invalid input.  Try again (Type nuber from 1 to 7): ", 1, 7);
    Person::Category category = static_cast<Person::Category>(input - 1);
    trip_to_init.get_person(person_id - 1).set_att(category);
    system("CLS");
    std::cout << "AFTER CHANGE:\n" << trip_to_init.get_person(person_id - 1).print_atts();
    std::cout << "Do you want to change anything else? [Y/N] \n";
    std::string answer;
    while (!check_yes_no_input(answer))
    {
        std::cin >> answer;
    }
    if (is_positive(answer))
        set_attributes(trip_to_init, person_id);
    else
        interface(trip_to_init);
}

void add_transactions(Trip &trip)
{
    system("CLS");
    if (!trip.get_people_size())
    {
        std::cout << "\nAdd people before adding transactions";
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(10, '\n');
        std::cin.get();
        interface(trip);
        return;
    }
    std::cout << "\nAdd transactions:\n";
    std::cout << "Choose options:\n";
    std::cout << "1. Add collective transaction(all participants included).(Type '1')\n";
    std::cout << "2. Add specific transaction with limited number of participants.(Type '2')\n";
    int input = numerical_input("Invalid input.  Try again (Type 1 or 2): ", 1, 2);
    if(input == 1)
        add_collective_transaction(trip);
    else
        add_specific_transaction(trip);
    interface(trip);
}


void add_singular_transaction()
{
    std::cout << "\nAdd singular transactions:\n";
    //TODO
}

std::string print_categories()
{
    std::string output;
    for (int i = 0; i <= 6; i++)
    {
        Person::Category cat = static_cast<Person::Category>(i);
        output += std::to_string(i + 1) + ". " + Person::Cat_to_str(cat) + "\n";
    }
    return output;
}

void add_collective_transaction(Trip& trip)
{

    system("CLS");
    std::cout << "\nAdd collective transaction:\n";
    std::cout << "Select payer id: \n ";
    trip.print_people(std::cout);
    int size = trip.get_people_size();
    std::string message = "Invalid input.  Try again (Type number from 1 to " + std::to_string(size) + "): ";
    int payer_id = numerical_input(message, 1, size);
    std::cout << "\nType the category number:\n";
    std::cout << print_categories();
    int category_number = numerical_input("Invalid input.  Try again (Type number from 1 to 7): ", 1, 7);
    Person::Category category = static_cast<Person::Category>(category_number - 1);
    std::cout << "\nPlease enter payed amount\n";
    float money = numerical_input("Invalid input.  Try again (Type the amount): ", 0, 99999);
    try
    {
        std::shared_ptr<Transaction> transaction = std::make_shared<CollectiveTransaction>(money, payer_id, category);
        trip.add_transaction(transaction);
        std::cout << "\nTransaction added\n";
    }
    catch (my_excetpions)
    {
        std::cout << "\nNone of the people is included in that category, please try again";
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(10, '\n');
        std::cin.get();
        add_collective_transaction(trip);
    }
}

void add_specific_transaction(Trip &trip_to_init)
{
    std::cout << "\nAdd specific transaction:\n";
    //TODO
}

void settle(Trip& trip)
{
    std::cout << "Settlement Transfers:\n\n";
    std::map<std::pair<int, int>, float> trans_map = trip.calc_transfers();
    std::pair<int, std::pair<int,int>> *ids = new std::pair<int, std::pair<int,int>>[trans_map.size()];
    if (trans_map.size() == 0)
    {
        std::cout << "Everybody even!\n\n";
        interface(trip);
    }
    int i = 0;
    for (const std::pair<std::pair<int, int>, float>& pa: trans_map)
    {
        std::pair<int, std::pair<int,int>> id;
        std::cout << i + 1 << ". ";
        std::cout << "[" << trip.get_person(pa.first.first - 1).get_name() << " -> ";
        std::cout << trip.get_person(pa.first.second - 1).get_name() << "]: ";
        std::cout << pa.second << '\n';
        id.first = i;
        id.second = pa.first;
        *(ids + i) = id;
        i++;
    }
    std::cout << '\n';
    std::cout << "Would you like to settle any debt? [Y or N]\n";
    std::string answer;
    std::cin >> answer;
    while (!check_yes_no_input(answer))
    {
        std::cout << "Wrong input, type Y or N\n";
        answer = std::string();
        std::cin >> answer;
    }
    if (check_yes_no_input(answer))
         if (is_positive(answer))
            {
                std::cout << "Which debt do you want to settle? [insert debt number or 0 to exit]\n";
                int input = 0;
                while(!(std::cin >> input)){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input, try again! ";
                }
                if (input == 0)
                {
                    delete [] ids;
                    return interface(trip);
                }
                if (check_init_action(input, i + 1))
                    {
                        SpecificTransaction trans(trans_map[ids[input - 1].second], ids[input - 1].second.first,
                                                Person::Category::other, {ids[input - 1].second.second});
                        std::shared_ptr<Transaction> tptr = std::make_shared<SpecificTransaction>(trans);
                        trip.add_transaction(tptr);
                        std::cout << "Settled!\n";
                    }
                else
                    std::cout << "\nChoose proper option!\n";
            };
    delete [] ids;
    interface(trip);
}