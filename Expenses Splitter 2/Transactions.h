#include <string>
#include "Person.h"


class Transaction
{
    protected:
    double money;
    std::string category;
    Person payer;
    public:
    virtual void settle() const = 0;

};

class CollectiveTransaction: Transaction
{
    private:

    public:
};

class SpecificTransaction: Transaction
{
    private:
    public:
};