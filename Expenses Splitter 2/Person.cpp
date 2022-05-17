#include "Person.h"

Person::Person(unsigned int pid, std::string nm): id(pid), name(nm)
{
    balance = 0.0;
    atts["alcohol"] = true;
    atts["nicotine"] = false;
    atts["gluten"] = true;
    atts["meat"] = true;
    atts["dairy"] = true;
    atts["heavy_drinker"] = false;
}


bool Person::operator==(const Person &other) const
{
    return (atts == other.arg_str() && balance == other.get_balance()
            && name == other.get_name() && id == other.get_id());
}

bool Person::operator!=(const Person &other) const
{
    return !(*this == other);
}

std::string Person::file_input() const
{
    std::string instr;
    return instr;
}