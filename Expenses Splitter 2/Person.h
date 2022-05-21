#pragma once
#include <cmath>
#include <string>
#include <map>

class Person {
public:
	enum class Category { food, alcohol, nicotine, meat, gluten, dairy, other };
	static std::string Cat_to_str(Category c);
private:
	unsigned int id;
	std::string name;
	std::map<Category, bool> atts;
	// balance - sum of money to return/receive
	float balance;
public:
	Person(unsigned int pid, std::string nm);
	std::string get_name() const { return name; };
	float get_balance() const { return balance; };
	void set_balance(float newbal)  { balance = newbal; };
	void add_to_balace(float amount);
	int get_id() const { return id; };
	bool operator==(const Person& other) const;
	bool operator!=(const Person& other) const;
	//Brak sprawdzania warto�ci argument�w w setterach, poniewa� b�d� one sprawdzane osobnymi funkcjami

	void set_name(std::string new_name);
	void set_id(unsigned int new_id);
	
	void set_att(Category c, bool val) { atts[c] = val; }

	void atts_setter(std::string att_code);

	std::map<Category, bool> get_atts() const { return atts; };
    std::string file_input() const;
	bool category_compare(Category trans_c) const 
		//checks if person should be included in transaction of category c
	{
		std::map<Category, bool>::const_iterator elem = atts.find(trans_c);
		if (elem == atts.end())
			return false;
		return elem -> second;
	}
};
