#pragma once
#include <vector>
#include <memory>
#include "Database.h"
class Trip {
;	std::vector<Person> people;
	std::vector<std::shared_ptr<Transaction>> ptransactions;
public:
	Trip();
	void add_person(Person const&); //adds  person
	void add_transaction(std::shared_ptr<Transaction> p_trans); //adds pointer to transaction, settles peoples balances
	std::vector<Person> get_people()
	{
		return people;
	};
	std::vector<std::shared_ptr<Transaction>> get_ptransactions()
	{
		return ptransactions;
	};


};