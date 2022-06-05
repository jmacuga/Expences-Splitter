#include <string>
#include <cctype>
#include "ui_checks.h"

// sprawdzanie, czy ktoś nie podaje pustego imienia
bool check_name(std::string new_name)
{
    return(!new_name.empty());
}

// jeśli dane do ustawiania atrybutów alcohol, meat etc
// będą stringami, to sprawdzam, czy przyjmują, żadane wartości
// typu: "Yes", "No", "n" etc
bool check_yes_no_input(std::string input)
{
    for (auto c : input) c = toupper(c);
    return(input == "N" || input == "NO" || input == "Y" || input == "YES");
}

//check if the number typed is in given range
bool check_init_action(int input, int range )
{
    return (input >= 1 && input <= range);
}

//argument should be valid yes or no input
bool is_positive(std::string input)
{
<<<<<<< HEAD
    if (input == "Y" || input == "N")
        return true;
    else false;
}


bool check_atts_input(int input)
{
    if (input == 1 || input == 2 || input == 3 || input == 4 || input == 5 || input == 6 || input == 7)
        return true;
    else
        return false;
=======
    for (auto c : input) c = toupper(c);
    return (input == "Y" || input == "YES");
>>>>>>> d7b17119b6e361b028f6b0b4abae470c7e0f4a22
}