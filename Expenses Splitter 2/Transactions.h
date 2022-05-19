#pragma once
#include <string>
#include <vector>
#include "Person.h"

enum categories { food, alcohol, tabacco, meat, other };
enum my_excetpions {NegativeNumber, FileNotOpen};
class Transaction
{
protected:
    float money;
    int category;
    Person& payer;
public:
    Transaction(float m, Person& p, categories c) : money(m), category(c), payer(p) {
        if (m < 0)
            throw NegativeNumber;
    };
    Person& get_payer() const { return payer; };
    int get_category() const { return category; };
    float get_money() const { return money; };
    virtual std::vector<Person*> get_included() const {
        //default virtual function returns empty vector
        std::vector<Person*> v;
        return v;
    };
    virtual std::string file_input() const = 0;
    bool operator==(const Transaction& other) const ;
    bool operator!=(const Transaction& other) const { return !(*this == other); };
};


class CollectiveTransaction : public Transaction
{
public:
    CollectiveTransaction(float m, Person& p, categories c): Transaction(m, p, c) {};
    std::string file_input() const;
};

class SpecificTransaction : public CollectiveTransaction
{
private:
    std::vector<Person*> v_included;
public:
    SpecificTransaction(float m, Person& p, categories c, std::vector<Person*> v_incl) : CollectiveTransaction(m, p, c)
    { v_included = v_incl; };
    std::string file_input() const;
    std::vector<Person*> get_included() const { return v_included; };
    bool operator==(const SpecificTransaction& other) const;
};