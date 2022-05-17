#include "Trip.h"

void Trip::add_person(Person const& p)
{
	for (Person trip_p : people)
	{
		if (p == trip_p)
			return;
	}
	people.push_back(p);
}

void Trip::add_transaction(std::shared_ptr<Transaction> p_trans)
{
	ptransactions.push_back(p_trans);
}