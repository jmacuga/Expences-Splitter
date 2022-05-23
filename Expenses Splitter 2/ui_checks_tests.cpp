#include <iostream>
#include "ui_checks.cpp"


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
    if(check_set_att_input("N") == true)
        return true;
    else
    {
        std::cout << "\nerror in test_check_set_att_input_1\n";
        return false;
    }
}

bool test_check_set_att_input_2()
{
    if(check_set_att_input("Y") == true)
        return true;
    else
    {
        std::cout << "\nerror in test_check_set_att_input_2\n";
        return false;
    }
}

bool test_check_set_att_input_3()
{
    if(check_set_att_input("NO") == true)
        return true;
    else
    {
        std::cout << "\nerror in test_check_set_att_input_3\n";
        return false;
    }
}

bool test_check_set_att_input_4()
{
    if(check_set_att_input("YES") == true)
        return true;
    else
    {
        std::cout << "\nerror in test_check_set_att_input_4\n";
        return false;
    }
}

bool test_check_set_att_input_5()
{
    if(check_set_att_input("si") == false)
        return true;
    else
    {
        std::cout << "\nerror in test_check_set_att_input_5\n";
        return false;
    }
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

    if(flag == false)
        std::cout << "\nErrors in tests.\n";
    else
        std::cout << "\nAll tests passed.\n";

    std::cout << "\nEnd of tests.\n";

    return 0;
}
