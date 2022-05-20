#include "Trip.h"
#include "Transactions.h"
#include <iostream>
#include <fstream>
#include<typeinfo>

void Trip::add_person(Person const& p)
{
	for (Person trip_p : people)
	{
		if (p == trip_p)
			return;
	}
	people.push_back(p);
}
//adds transaction to p_trans, changes payer balance and other people balances
void Trip::add_transaction(std::shared_ptr<Transaction> p_trans)
{
	if (p_trans == nullptr)		return;
	ptransactions.push_back(p_trans);
	float money = p_trans->get_money();
	float moneypp = 0;
	size_t incl_number = p_trans->get_included().size();
	if (incl_number)
	{
		moneypp = money/(incl_number + 1);
		for (Person* p : p_trans->get_included())
		{
			p->add_to_balace(-moneypp);
		}
	}
	else
	{
		moneypp = money/people.size();
		for (Person p : people)
		{
			if (p == p_trans->get_payer()) continue;
			p.add_to_balace(-moneypp);
		}
	}
	p_trans->get_payer().add_to_balace(money - moneypp);
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
	auto pderived = [&myfile](std::string fline)
	{
		std::string line = fline;
		std::string sid = "";
		std::string name = "";
		std::string sbalance = "";
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
		getline(myfile, line);
		per.atts_setter(line);
		getline(myfile, line);
		if (line != "")
			throw WrongFileFormat;
		return per;
	};

	if (!myfile.is_open())
		throw FileNotOpen;
	std::string line = "";
	while (line != "PEOPLE")
		getline(myfile, line);
	getline(myfile, line);
	if (line != "")
		throw WrongFileFormat;
	while (true)
	{
		getline(myfile, line);
		if (line == "TRANSACTIONS")
			break;
		people.push_back(pderived(line));
	}

}