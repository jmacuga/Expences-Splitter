#include "Transactions.h"
#include "Trip.h"
#include "sstream"


std::string CollectiveTransaction::file_input() const
{
    std::stringstream rets;
    rets << "COL\n" << time << "\n" << payer << "\n" << money;
    rets << "\n" << int(category) << "\n";
    return rets.str();
}

std::string SpecificTransaction::file_input() const
{
    std::stringstream rets;
    std::string tst = "";
    rets << "SPE\n" << time << "\n" << payer << "\n" << money;
    rets << "\n" << int(category) << "\n";
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
