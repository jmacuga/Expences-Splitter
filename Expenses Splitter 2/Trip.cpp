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
	myfile <<  name << "\n\n";
	myfile << "PEOPLE\n\n";
	for (const Person &p: people)
		myfile << p.file_input() << '\n';
	myfile << "TRANSACTIONS\n\n";
	for (const std::shared_ptr<Transaction> &tr: ptransactions)
		myfile << tr->file_input() << '\n';

}

void Trip::load_from_file(std::ifstream &myfile)
{
	auto pderived = [&myfile]()
	{
		std::string line;
		std::string sid = "";
		std::string name = "";
		std::string sbalance = "";
		getline(myfile, line);
		bool space_met = false;
		for(const char &c: line)
		{
			if (c == ' ')
			{
				space_met = true;
				continue;
			}
			if (!space_met)
				sid += c;
			else
				name += c;
		}
		Person per(stoi(sid), name);
		getline(myfile, line);
		for(const char &c: line)
			sbalance += c;
		per.set_balance(stod(sbalance));
		return per;
	};

	if (!myfile.is_open())
		throw FileNotOpen;

}