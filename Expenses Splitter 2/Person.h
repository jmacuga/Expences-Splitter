#pragma once
#include <cmath>
#include <string>
#include <map>

class Person {
public:
	enum class Category { food, alcohol, nicotine, meat, gluten, other };
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
	
	void set_att_true(Category c)
	{
		atts[c] = true; 
	}

	void set_att_false(Category c)
	{
		atts[c] = false;
	}

	//void set_alcohol(bool bl) { atts["alcohol"] = bl; }
	//void set_nicotine(bool bl) { atts["nicotine"] = bl; }
	//void set_gluten(bool bl) { atts["gluten"] = bl; }
	//void set_meat(bool bl) { atts["meat"] = bl; }
	//void set_dairy(bool bl) { atts["dairy"] = bl; }
	//void set_heavy_drinker(bool bl) { atts["heavy_drinker"] = bl; }

	void atts_setter(std::string att_code);
	
	//bool get_alcohol() { return atts["alcohol"]; };
	//bool get_nicotine() { return atts["nicotine"]; };
	//bool get_gluten() { return atts["gluten"]; };
	//bool get_meat() { return atts["meat"]; };
	//bool get_dairy() { return atts["dairy"]; };
	//bool get_heavy_drinker() { return atts["heavy_drinker"]; };

	std::map<Category, bool> get_atts() const { return atts; };
    std::string file_input() const;
};
