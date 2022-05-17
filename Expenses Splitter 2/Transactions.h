#pragma once
#include <string>
#include "Person.h"

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
    //virtual void settle() const = 0;

};

class CollectiveTransaction : public Transaction
{
private:

public:
    CollectiveTransaction(double m, Person p, categories c) : Transaction(m, p, c) {};
};

class SpecificTransaction : public Transaction
{
private:
public:
};