#include "Trip.h"
#include "Transactions.h"
#include <iostream>
#include <fstream>

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
	if (!myfile.is_open())
		throw FileNotOpen;
	myfile << "PEOPLE\n\n";
	for (const Person &p: people)
		myfile << p.file_input() << '\n';
	myfile << "TRANSACTIONS\n\n";
	for (const std::shared_ptr<Transaction> &tr: ptransactions)
		myfile << tr->file_input() << '\n';

}

void Trip::load_from_file(std::ifstream &myfile)
{

}