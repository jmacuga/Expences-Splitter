#include <string>
#include <cctype>
#include <iostream>
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
    for (auto& c : input) c = toupper(c);
    return(input == "N" || input == "NO" || input == "Y" || input == "YES");
}


//argument should be valid yes or no input
bool is_positive(std::string input)
{
    for (auto& c : input) c = toupper(c);
    return (input == "Y" || input == "YES");
}

//checks if input is valid and returns bool value of yes/no answer
bool is_input_positive()
{
    std::string input;  
    std::cin >> input;
    for (auto& c : input) c = toupper(c);
    while (!(input == "N" || input == "NO" || input == "Y" || input == "YES"))
    {
        std::cout << "Invalid input. (enter Y or N): ";
        std::cin >> input;
        for (auto& c : input) c = toupper(c);
    }
    return (input == "Y" || input == "YES") ;
}   