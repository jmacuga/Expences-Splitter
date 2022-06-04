#include <iostream>
#include "ui_checks.h"
#include "ui_actions.h"


bool test_check_name_1()
{
    if(check_name("") == false)
        return true;
    else
    {
        std::cout << "\nerror in test_check_name_1\n";
        return false;
    }
}


bool test_check_name_2()
{
    if(check_name("Piotr") == true)
        return true;
    else
    {
        std::cout << "\nerror in test_check_name_1\n";
        return false;
    }
}

bool test_check_set_att_input_1()
{
    if(check_yes_no_input("N") == true)
        return true;
    else
    {
        std::cout << "\nerror in test_check_set_att_input_1\n";
        return false;
    }
}

bool test_check_set_att_input_2()
{
    if(check_yes_no_input("Y") == true)
        return true;
    else
    {
        std::cout << "\nerror in test_check_set_att_input_2\n";
        return false;
    }
}

bool test_check_set_att_input_3()
{
    if(check_yes_no_input("NO") == true)
        return true;
    else
    {
        std::cout << "\nerror in test_check_set_att_input_3\n";
        return false;
    }
}

bool test_check_set_att_input_4()
{
    if(check_yes_no_input("YES") == true)
        return true;
    else
    {
        std::cout << "\nerror in test_check_set_att_input_4\n";
        return false;
    }
}

bool test_check_set_att_input_5()
{
    if(check_yes_no_input("si") == false)
        return true;
    else
    {
        std::cout << "\nerror in test_check_set_att_input_5\n";
        return false;
    }
}

bool test_load_history()
{
    return true;
}

bool test_value_bool()
{
    return !is_positive("NO");
}


int main()
{
    bool flag = true;
    flag = flag && test_check_name_1();
    flag = flag && test_check_name_2();
    flag = flag && test_check_set_att_input_1();
    flag = flag && test_check_set_att_input_2();
    flag = flag && test_check_set_att_input_3();
    flag = flag && test_check_set_att_input_4();
    flag = flag && test_check_set_att_input_5();
    flag = flag && test_value_bool();

    if(flag == false)
        std::cout << "\nErrors in tests.\n";
    else
        std::cout << "\nAll tests passed.\n";

    std::cout << "\nEnd of tests.\n";
    Trip trip("200 osob w kawalerce");
    launch_app(trip);
    return 0;
}
