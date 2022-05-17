#pragma once
#include "Transactions.h"
#include <vector>

template <typename T> class Database
{
private:
    std::vector<T> collection;
public:
    void save_into_file(std::string path) const;
    void load_from_file(std::string path) const;
    void operator+=(T elem)
    {
        collection.push_back(elem);
    };
    T& operator[](int ind)
    {
        return collection[ind];
    };

};