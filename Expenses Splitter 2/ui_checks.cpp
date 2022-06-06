#include <string>
#include <cctype>
#include <iostream>
#include "ui_checks.h"

//checks if input is valid and returns 
bool is_input_positive()
{
    std::string input;  
    while (true)
    {
        std::cin >> input;
        for (auto& c : input) c = toupper(c);
        if (input == "N" || input == "NO" || input == "Y" || input == "YES")
            break;
        std::cout << "Invalid input. (enter Y or N): ";
    }
    return (input == "Y" || input == "YES") ;
}   

