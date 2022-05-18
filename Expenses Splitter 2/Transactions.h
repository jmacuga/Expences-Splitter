#pragma once
#include <string>
#include "Person.h"
#include <vector>

enum categories { food, alcohol, tabacco, meat, other };
enum my_excetpions { NegativeNumber};
class Transaction
{
protected:
    double money;
    int category;
    Person& payer;
public:
    Transaction(double m, Person& p, categories c) : money(m), category(c), payer(p) {
        if (m < 0)
            throw NegativeNumber;
    };
    Person& get_payer() { return payer; };
    int get_category() { return category; };
    double get_money() { return money; };
    virtual std::string file_input() const = 0;
};


class CollectiveTransaction : public Transaction
{
public:
    CollectiveTransaction(double m, Person& p, categories c): Transaction(m, p, c) {};
    std::string file_input() const;
};

class SpecificTransaction : public Transaction
{
private:
    std::vector<Person*> v_included;
public:
    SpecificTransaction(double m, Person& p, categories c, std::vector<Person*> v_incl) : Transaction(m, p, c)
    { v_included = v_incl; };
    std::string file_input() const;
};