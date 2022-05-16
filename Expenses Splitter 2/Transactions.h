#pragma once
#include <string>
#include "Person.h"

enum categories { food, alcohol, tabacco, other };
class Transaction
{
protected:
    double money;
    int category;
    Person payer;
public:
    Transaction(double m, Person p, categories c) : money(m), category(c), payer(p) {};
    virtual void settle() const = 0;

};

class CollectiveTransaction : Transaction
{
private:

public:
    CollectiveTransaction(double m, Person p, categories c) : Transaction(m, p, c) {};
    void settle() const {};
};

class SpecificTransaction : Transaction
{
private:
public:
};