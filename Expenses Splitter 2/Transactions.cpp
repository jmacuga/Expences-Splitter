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

std::string SpecificTransaction::file_input() const
{
    std::stringstream rets;
    rets << "SPE\n" << payer.get_id() << "\n" << money << "\n" << category << "\n";
    for (const Person* p: v_included)
        rets << p->get_id();
    rets << "\n";
    return rets.str();
}

