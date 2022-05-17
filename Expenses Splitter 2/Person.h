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

   //Brak sprawdzania wartości argumentów w setterach, ponieważ będą one sprawdzane osobnymi funkcjami

  void set_name(std::string new_name);
  void set_id(unsigned int new_id);
  void set_alcohol(bool bl) {atts["alcohol"] = bl;}
  void set_nicotine(bool bl) {atts["nicotine"] = bl;}
  void set_gluten(bool bl) {atts["gluten"] = bl;}
  void set_meat(bool bl) {atts["meat"] = bl;}
  void set_dairy(bool bl) {atts["dairy"] = bl;}
  void set_heavy_drinker(bool bl) {atts["heavy_drinker"] = bl;}

  std::unordered_map<std::string, bool> arg_str() const { return atts; };
};
