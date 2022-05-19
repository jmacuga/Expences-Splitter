#include "Transactions.h"
#include "sstream"

/*
    File input format:
    Type of transaction - COL or SPE
    Payer's ID
    Transaction's amount
    Transaction's category (int connected to a given enum)
    (only SPE) Recievers ID's
*/
std::string CollectiveTransaction::file_input() const
{
    std::stringstream rets;
    rets << "COL\n" << payer.get_id() << "\n" << money << "\n" << category << "\n";
    return rets.str();
}

std::vector<Person*> SpecificTransaction::get_v_included() const
{
    return v_included;
}
std::string SpecificTransaction::file_input() const
{
    std::stringstream rets;
    rets << "SPE\n" << payer.get_id() << "\n" << money << "\n" << category << "\n";
    for (const Person* p: v_included)
        rets << p->get_id();
    rets << "\n";
    return rets.str();
}

bool CollectiveTransaction::operator==(const CollectiveTransaction& other) const
{
    return (money == other.get_money() &&
            payer == other.get_payer() &&
            category == other.get_category());
}

bool SpecificTransaction::operator==(const SpecificTransaction& other) const
{
    return (CollectiveTransaction::operator==(other) && v_included == other.get_included());
}

