#pragma once
#include <string>
#include "Person.h"
#include <vector>

enum categories { food, alcohol, tabacco, other };
enum my_excetpions { NegativeNumber};
class Transaction
{
protected:
    double money;
    int category;
    Person payer;
public:
    Transaction(double m, Person p, categories c) : money(m), category(c), payer(p) {
        if (m < 0)
            throw NegativeNumber;
    };

};

class SpecificTransaction : public Transaction
{
    private:
        std::vector<Person*> recievers;
    public:
        SpecificTransaction(double m, Person p, categories c, std::vector<Person*> rec):
        Transaction(m, p, c), recievers(rec) {}
};