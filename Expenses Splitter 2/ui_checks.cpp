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
bool check_set_att_input(std::string set_attr)
{
    for (auto& c : set_attr) c = toupper(c);
    if(set_attr == "N" || set_attr == "NO" || set_attr == "Y" || set_attr == "YES")
        return true;
    else
        return false;
}

bool check_init_action(int input)
{
    if (input == 1 || input == 2 || input == 3 || input == 4 || input == 5 || input == 6)
        return true;
    else
        return false;
}


bool check_init_action_2_opt(int input)
{
    if (input == 1 || input == 2)
        return true;
    else
        return false;
}

bool check_answer_atts(std::string input)
{
    for (auto& c : input) c = toupper(c);
    if (input == "Y" || input == "N")
        return true;
    else false;
}
