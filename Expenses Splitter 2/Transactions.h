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
    Transaction(float m, int p, Person::Category c, std::time_t t = std::time(0)):
                money(m), category(c), payer(p), time(t) {
        if (m < 0)
            throw NegativeNumber;
    };
    int get_payer() const { return payer; };
    Person::Category get_category() const { return category; };
    float get_money() const { return money; };
    const std::time_t* get_time() const { return &time; };
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
    CollectiveTransaction(float m, int p, Person::Category c, std::time_t t = std::time(0)):
                          Transaction(m, p, c, t) {};
    std::string file_input() const;
};

class SpecificTransaction : public CollectiveTransaction
{
private:
    std::vector<int> inid;
public:
    SpecificTransaction(float m, int p, Person::Category c, std::vector<int> incl_ids, std::time_t t = std::time(0)):
                        CollectiveTransaction(m, p, c, t)
    { inid = incl_ids; };
    std::string file_input() const;
    std::vector<int> get_included() const { return inid; };
    bool operator==(const SpecificTransaction& other) const;
};