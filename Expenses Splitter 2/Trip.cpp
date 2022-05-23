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
	std::vector<Person*> included;
	if(!incl_number)
	{
		for (Person& p : people)
		{
			if (p.category_compare(p_trans->get_category()))
			{
				incl_number++;
				included.push_back(&p);
			}
		}
	}
	else
	{
		for (int &idx: p_trans->get_included())
			included.push_back(&people[idx - 1]);
	}
	moneypp = money/(incl_number);
	for (Person* p : included)
	{
		p->add_to_balace(-moneypp);
	}
	people[p_trans->get_payer() - 1].add_to_balace(money);
}

void Trip::save_to_file(std::ofstream &myfile) const
{
	if (!myfile.is_open())
		throw FileNotOpen;
	myfile <<  name << "\n\n";
	myfile << "PEOPLE\n\n";
	for ( const Person &p : people)
		myfile << p.file_input() << '\n';
	myfile << "TRANSACTIONS\n\n";
	for (const std::shared_ptr<Transaction> &tr: ptransactions)
		myfile << tr->file_input() << '\n';
	myfile << "&&&";

}

void Trip::load_from_file(std::ifstream &myfile)
{
	auto pderived = [&myfile](std::string fline)
	{
		std::string line = fline;
		std::string sid = "";
		std::string name = "";
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
		per.atts_setter(line);
		getline(myfile, line);
		if (line != "")
			throw WrongFileFormat;
		return per;
	};

	auto coltderived = [&myfile, this]()
	{
		std::string line;
		double balance;
		int payer;
		Person::Category cat;
		getline(myfile, line);
		payer = stoi(line);
		getline(myfile, line);
		balance = stod(line);
		getline(myfile, line);
		cat = Person::Category(stoi(line));
		getline(myfile, line);
		return CollectiveTransaction(balance, payer, cat);
	};

	auto spetderived = [&myfile, this]()
	{
		std::string line;
		double balance;
		int payer;
		Person::Category cat;
		getline(myfile, line);
		payer = stoi(line);
		getline(myfile, line);
		balance = stod(line);
		getline(myfile, line);
		cat = Person::Category(stoi(line));
		getline(myfile, line);
		std::vector<int> recievers(line.length());
		size_t idx = 0;
		for (const char &c: line)
		{
			recievers[idx] = (int)c - '0';
			idx++;
		}
		getline(myfile, line);
		return SpecificTransaction(balance, payer, cat, std::vector<int>(recievers));
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
	getline(myfile, line);
	getline(myfile, line);
	while (line != "&&&")
	{
		if (line == "COL")
		{
			add_transaction(std::make_shared<CollectiveTransaction>(coltderived()));
			getline(myfile, line);
		}
		else if (line == "SPE")
		{
			add_transaction(std::make_shared<SpecificTransaction>(spetderived()));
			getline(myfile, line);
		}
		else
			throw WrongFileFormat;
	}

}