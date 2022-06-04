#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "Transactions.h"

class Trip {
private:
	std::vector<Person> people;
	std::vector<std::shared_ptr<Transaction>> ptransactions;
	std::string name;
public:
// two Trip constructors, one with file handle to file from which should it be recreated
	Trip(std::string nm): name(nm) {};
	Trip(std::string nm, std::ifstream &myfile): name(nm) { load_from_file(myfile); };
	void add_person(Person const& p); //adds  person
	void add_transaction(std::shared_ptr<Transaction> p_trans); //adds pointer to transaction, settles peoples balances

	Person& get_person(int id) { return people[id]; }
	size_t get_people_size() { return people.size(); }
	float get_person_balance(int id) { return people[id].get_balance(); };
	std::string get_name() { return name; };

	void save_to_file(std::ofstream &myfile) const;
	void load_from_file(std::ifstream &myfile);
	std::map<std::pair<int, int>, float> calc_transfers();
	static void split_money(std::vector<std::pair<int, float>>& first_bufor,
		std::vector<std::pair<int, float>>& second_bufor,
		std::map<std::pair<int, int>, float>& result, bool is_first_negative = false);

	// TODO zaimplementować takie funkcje, przydadzą się w ui
	std::ostream& print_people(std::ostream &os);
	std::ostream& print_trans(std::ostream &os);
};