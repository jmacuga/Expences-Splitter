#pragma once
#include <string>
#include <vector>
#include <ctime>
#include "Person.h"

enum my_excetpions {NegativeNumber, FileNotOpen, WrongFileFormat, WrongCategory};
class Transaction
{
public:
    static bool fl_cmp(const float& fst, const float& scnd)
    {
        return std::abs(fst - scnd) < 10e-4;
    };
protected:
    float money;
    Person::Category category;
    int payer;
    std::time_t time;
public:
    Transaction(float m, int p, Person::Category c) : money(m), category(c), payer(p) {
        if (m < 0)
            throw NegativeNumber;
        time = std::time(0);
    };
    int get_payer() const { return payer; };
    Person::Category get_category() const { return category; };
    float get_money() const { return money; };
    std::time_t get_time() const { return time; }; 
    virtual std::vector<int> get_included() const {
        //default virtual function returns empty vector
        std::vector<int> v;
        return v;
    };
    virtual std::string file_input() const = 0;
    bool operator==(const Transaction& other) const;
    bool operator!=(const Transaction& other) const { return !(*this == other); };
};


class CollectiveTransaction : public Transaction
{
public:
    CollectiveTransaction(float m, int p, Person::Category c): Transaction(m, p, c) {};
    std::string file_input() const;
};

class SpecificTransaction : public CollectiveTransaction
{
private:
    std::vector<int> inid;
public:
    SpecificTransaction(float m, int p, Person::Category c, std::vector<int> incl_ids) : CollectiveTransaction(m, p, c)
    { inid = incl_ids; };
    std::string file_input() const;
    std::vector<int> get_included() const { return inid; };
    bool operator==(const SpecificTransaction& other) const;
};