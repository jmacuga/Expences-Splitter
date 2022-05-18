#pragma once
#include "Transactions.h"
#include <vector>

template < typename T> class Database
{
private:
public:
    void save_into_file(std::string path) const;
    void load_from_file(std::string path) const;
};