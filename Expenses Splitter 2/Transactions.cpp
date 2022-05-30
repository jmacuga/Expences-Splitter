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
    rets << "SPE\n" << payer << "\n" << money << "\n" << int(category) << "\n";
    for (const int &id: inid)
        rets << id;
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
    return (CollectiveTransaction::operator==(other) && inid == other.get_included());
}

std::ostream& Transaction::print(std::ostream &os, Trip const& trip) const
{
    os << "Date:" << '\n';
    os << "Paid: " << trip.people.at(payer - 1).get_name() << '\n';
    os << "Amount: " << money << '\n';
    os << "Category: " << '\n';
    return os;
}

std::ostream& CollectiveTransaction::print(std::ostream &os, Trip const& trip) const
{
    os << "Type: Collective\n";
    Transaction::print(os, trip);
    return os;
}

std::ostream& SpecificTransaction::print(std::ostream &os, Trip const& trip) const
{
    os << "Type: Specific\n";
    Transaction::print(os, trip);
    os << "For: ";
    for (int id: inid)
    {
        os << trip.people.at(id - 1).get_name() << ", ";
    }
    os.seekp(-2, std::ios_base::end);
    os << " \n";
    return os;
}
