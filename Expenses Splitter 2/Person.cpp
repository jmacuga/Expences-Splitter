#include <cmath>
#include <sstream>
#include "Person.h"

Person::Person(unsigned int pid, std::string nm) : id(pid), name(nm)
{
    balance = 0.0;
    atts["alcohol"] = true;
    atts["nicotine"] = false;
    atts["gluten"] = true;
    atts["meat"] = true;
    atts["dairy"] = true;
    atts["heavy_drinker"] = false;
}


bool Person::operator==(const Person& other) const
{
    return (atts == other.arg_str() && balance == other.get_balance()
        && name == other.get_name() && id == other.get_id());
}

bool Person::operator!=(const Person& other) const
{
    return !(*this == other);
}


void Person::add_to_balace(float price)
{
    balance += price;
}

std::string Person::file_input() const
{

    std::stringstream instr;
    instr << id << " " << name << '\n';
    instr << balance << '\n';
    for (std::pair<const std::string, bool> pa: atts)
        instr << int(std::get<1>(pa));
    instr << '\n';
    return instr.str();
}