#include "Trip.h"
#include <iostream>
#include <fstream>

Trip::Trip()
{
	
}
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

	p_trans->get_payer().add_to_balace(p_trans->get_money());
	ptransactions.push_back(p_trans);
}

void Trip::save_to_file(std::ofstream &myfile) const
{

}

void Trip::load_from_file(std::ifstream &myfile)
{

}