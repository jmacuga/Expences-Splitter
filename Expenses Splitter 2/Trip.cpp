#include "Trip.h"
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
	size_t incl_number = p_trans->get_v_included().size();
	if (incl_number)
	{
		moneypp = money/(incl_number + 1);
		for (Person* p : p_trans->get_v_included())
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

}

void Trip::load_from_file(std::ifstream &myfile)
{

}