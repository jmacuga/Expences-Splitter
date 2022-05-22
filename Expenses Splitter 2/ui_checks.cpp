#include <string>
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
    if(set_attr == "N" || set_attr == "NO" || set_attr == "Y" || set_attr == "YES")
        return true;
    else
        return false;
}

bool check_init_action(int input)
{
    if (input == 1 || input == 2 || input == 3)
        return true;
    else
        return false;
}
