#include "Transactions.h"
#include "Trip.h"
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
    rets << "COL\n" << payer << "\n" << money << "\n" << int(category) << "\n";
    return rets.str();
}

std::string SpecificTransaction::file_input() const
{
    std::stringstream rets;
    std::string tst = "";
    rets << "SPE\n" << payer << "\n" << money << "\n" << int(category) << "\n";
    tst = rets.str();
    for (const int &id: inid)
        rets << id;
    rets << "\n";
    tst = rets.str();
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
    return (CollectiveTransaction::operator==(other) && inid == other.get_included());
}
