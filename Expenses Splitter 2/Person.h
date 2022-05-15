#pragma once

#include "Trip.h"
#include <string>
#include <unordered_map>

class Person {
  unsigned int id;
  std::string name;
  std::unordered_map<std::string, bool> atts;
  // balance - sum of money to return/receive
  double balance;

public:
  Person(unsigned int pid, std::string nm);
  void alc_false() { atts["alcohol"] = false; };
  void hd_true() { atts["heavy_drinker"] = true; }
  std::string get_name() const { return name; };
  double get_balance() const { return balance; };
  int get_id() const { return id; };
  bool operator==(const Person &other) const;
  bool operator!=(const Person &other) const;
  std::unordered_map<std::string, bool> arg_str() const { return atts; };
};
