#include "Trip.h"
#include "Transactions.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include<typeinfo>

void Trip::add_person(Person const& p)
{
	for (Person trip_p : people)
		if (p == trip_p) 
			return;
	people.push_back(p);
}
//adds transaction to p_trans, changes payer balance and other people balances
void Trip::add_transaction(std::shared_ptr<Transaction> p_trans)
{
	if (p_trans == nullptr)	
		return;
	ptransactions.push_back(p_trans);
	float money = p_trans->get_money();
	float moneypp = 0;
	size_t incl_number = p_trans->get_included().size();
	std::vector<Person*> included;
	if (!incl_number)
	{
		for (Person& p : people)
			if (p.category_compare(p_trans->get_category()))
			{
				incl_number++;
				included.push_back(&p);
			}
	} 
	else
	{
		for (int &idx: p_trans->get_included())
			included.push_back(&people[idx - 1]);
	}
		
	//in case if no one has certain category as true
	if (!incl_number) 
		return;
	moneypp = money/(incl_number);
	for (Person* p : included)
		p->add_to_balace(-moneypp);
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

std::map<std::pair<int, int>, float> Trip::calc_transfers()
{
	std::map<std::pair<int, int>, float> result;
	//lambda to compare pair by balance
	auto greater_pair = [](std::pair<int, float> const& p1, 
		std::pair<int, float> const& p2)
	{return abs(p2.second) > abs(p1.second); };
	//bufors of balances wich we will be zero at the end of func
	std::vector<std::pair<int, float>> pos_bufor;
	std::vector<std::pair<int, float>> neg_bufor;
	for (Person p : people)
	{
		if (!p.get_balance())	
			continue;
		auto pers_p = std::make_pair(p.get_id(), p.get_balance());
		if (pers_p.second > 0)
			pos_bufor.push_back(pers_p);
		else 
			neg_bufor.push_back(pers_p);
	}
	std::sort(pos_bufor.begin(), pos_bufor.end(), greater_pair);
	std::sort(neg_bufor.begin(), neg_bufor.end(), greater_pair);
	split_money(pos_bufor, neg_bufor, result);
	split_money(neg_bufor, pos_bufor, result, true);
	return result;
}

//helper func to calc_transfers()
void Trip::split_money(std::vector<std::pair<int, float>>& first_bufor,
	std::vector<std::pair<int, float>>& second_bufor,
	std::map<std::pair<int, int>, float>& result, bool is_first_negative)
{
	for (auto fit = first_bufor.begin(); fit != first_bufor.end(); fit++)
	{
		if (!fit->second)	
			continue;
		for (auto sit = second_bufor.begin(); sit != second_bufor.end(); sit++)
		{
			if (abs(sit->second) && abs(sit->second) <= abs(fit->second))
			{
				if (is_first_negative)
					result.insert({ {fit->first, sit->first}, abs(sit->second) });
				else
					result.insert({ {sit->first, fit->first}, abs(sit->second) });
				fit->second += sit->second;
				sit->second = 0;
			}
		}
	}
}

std::ostream& Trip::print_people(std::ostream &os)
{
	os << "People list:\n";
	for (Person& per: people)
	{
		os << per.get_id() << ". " << per.get_name() << '\n';
		os << "Balance: " << per.get_balance() << '\n';
	}
	os << '\n';
	return os;
}

std::ostream& Trip::print_trans(std::ostream &os)
{
	os << "Transactions history:\n\n";
	std::stringstream trstr;
	std::string line = "";
	for (std::shared_ptr<Transaction>& trans: ptransactions)
	{
		trstr << trans -> file_input();
		getline(trstr, line);
		if (line == "COL")
			os << "Type: Collective\n";
		else if (line == "SPE")
			os << "Type: Specific\n";
		getline(trstr, line);
		os << "Paid: " << people.at(stoi(line) - 1).get_name() << '\n';
		getline(trstr, line);
		os << "Amount: " << line << '\n';
		getline(trstr, line);
		os << "Category: to implement" << '\n';
		getline(trstr, line);
		if (line != "")
		{
			os << "For: ";
			int i = 1;
			for (char const& c: line)
			{
				os << people.at((int)c - '0' - 1).get_name();
				if (i < line.length())
					os << ", ";
				i++;
			}
			os << "\n\n";
		}
		else
			os << "\n";
	}
	return os;
}