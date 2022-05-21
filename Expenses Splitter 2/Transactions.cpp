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
//bool db_cmp(const double& fst, const double& scnd)
//{ return abs(fst - scnd) < 10e-8; }

std::string CollectiveTransaction::file_input() const
{
    std::stringstream rets;
    rets << "COL\n" << payer.get_id() << "\n" << money << "\n" << Person::Cat_to_str(category) << "\n";
    return rets.str();
}

std::string SpecificTransaction::file_input() const
{
    std::stringstream rets;
    rets << "SPE\n" << payer.get_id() << "\n" << money << "\n" << Person::Cat_to_str(category) << "\n";
    for (const Person* p: v_included)
        rets << p->get_id();
    rets << "\n";
    return rets.str();
}

bool Transaction::operator==(const Transaction& other) const
{
    return (Transaction::fl_cmp(money, other.get_money()) &&
            payer == other.get_payer() &&
            category == other.get_category());
}


bool SpecificTransaction::operator==(const SpecificTransaction& other) const
{
    return (CollectiveTransaction::operator==(other) && v_included == other.get_included());
}

