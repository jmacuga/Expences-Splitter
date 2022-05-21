#include <cmath>
#include <sstream>
#include "Person.h"
#include "Transactions.h"

Person::Person(unsigned int pid, std::string nm) : id(pid), name(nm)
{
    balance = 0.0;
    atts[Category::food] = true;
    atts[Category::alcohol] = true;
    atts[Category::nicotine] = false;
    atts[Category::meat] = true;
    atts[Category::gluten] = true;
    atts[Category::other] = true;
}

void Person::atts_setter(std::string att_code)
{
    std::string::const_iterator code_iter = att_code.cbegin();
    std::map<Category, bool>::iterator at_iter = atts.begin();
    for (code_iter, at_iter; at_iter != atts.end(); ++code_iter, ++at_iter)
        if (*(code_iter) == '1')
            (*at_iter).second = true;
        else if (*(code_iter) == '0')
            (*at_iter).second = false;
        else
            throw WrongFileFormat;
    if (at_iter != atts.end() && code_iter != att_code.cend())
        throw WrongFileFormat;
}

bool Person::operator==(const Person& other) const
{
    return (atts == other.get_atts() && Transaction::fl_cmp(balance, other.get_balance())
        && name == other.get_name() && id == other.get_id());
}

bool Person::operator!=(const Person& other) const
{
    return !(*this == other);
}


void Person::add_to_balace(float amount)
{
    balance += amount;
}

std::string Person::file_input() const
{

    std::stringstream instr;
    instr << id << " " << name << '\n';
    for (std::pair<const Category, bool> pa: atts)
        instr << int(std::get<1>(pa));
    instr << '\n';
    return instr.str();
}

std::string Person::Cat_to_str(Category c)
{
    switch (c) {
    case Category::food:
        return "food";
        break;
    case Category::nicotine:
        return "nicotine";
        break;
    case Category::meat:
        return "meat";
        break;
    case Category::gluten:
        return "gluten";
        break;
    case Category::other:
        return "other";
        break;
    default:
        return "NOT_A_CATEGORY";
    }
}
