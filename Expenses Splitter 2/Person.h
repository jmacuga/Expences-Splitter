#pragma once
#include <cmath>
#include <map>
#include <string>


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
  void set_balance(float newbal) { balance = newbal; };
  void add_to_balace(float amount);
  int get_id() const { return id; };
  bool operator==(const Person &other) const;
  bool operator!=(const Person &other) const;

  void set_att(Category c, bool val) { atts[c] = val; }
  void set_att(Category c) { atts[c] = !atts[c]; }
  std::map<Category, bool> get_atts() const { return atts; };

  void atts_setter(std::string att_code);
  std::string file_input() const;

  // checks if person should be included in transaction of category c
  bool category_compare(Category trans_c) const;
  std::string print_atts();
};
