#pragma once
#include <vector>
#include <memory>
#include "Transactions.h"

class Trip {
;	std::vector<Person> people;
	std::vector<std::shared_ptr<Transaction>> ptransactions;
	std::string name;
public:
// two Trip constructors, one with file handle to file from which should it be recreated
	Trip(std::string nm): name(nm) {};
	Trip(std::string nm, std::ifstream &myfile): name(nm) { load_from_file(myfile); };
	void add_person(Person const& p); //adds  person
	void add_transaction(std::shared_ptr<Transaction> p_trans); //adds pointer to transaction, settles peoples balances
	//TODO get_person(id) zeby nie zwracac calego wektora imo 
	std::vector<Person>* get_people() { return &people; };

	size_t get_trans_size() const { return ptransactions.size(); }
	Person const get_trans_payer(int trans_id) const { return ptransactions[trans_id]->get_payer(); };
	size_t get_people_size() { return people.size(); }
	float get_person_balance(int id) { return people[id].get_balance(); };	

	void save_to_file(std::ofstream &myfile) const;
	void load_from_file(std::ifstream &myfile);
};