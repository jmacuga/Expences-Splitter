#include <string>
#include <cctype>
#include "ui_checks.h"


// sprawdzanie, czy ktoś nie podaje pustego imienia
bool check_name(std::string new_name)
{
    if(new_name.empty())
        return false;
    return true;
}


// jeśli dane do ustawiania atrybutów alcohol, meat etc
// będą stringami, to sprawdzam, czy przyjmują, żadane wartości
// typu: "Yes", "No", "n" etc
// Z tym ze gdy uzytkownik wpisuje to dobrze sformatować tekst
// tak aby były np. zawsze duże litery, wtedy poniższe
//sprwadzania zadziałają
bool check_yes_no_input(std::string input)
{
    if(input == "N" || input == "NO" || input == "Y" || input == "YES")
        return true;
    else
        return false;
}

//check if the number typed is in given range
bool check_init_action(int input, int range )
{
    if (input >= 1  && input <= range)
        return true;
    else
        return false;
}

//argument should be valid yes or no input
bool is_positive(std::string input)
{
    return (input == "Y" || input == "YES");
}