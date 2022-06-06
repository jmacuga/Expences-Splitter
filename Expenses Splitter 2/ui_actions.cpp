#include "ui_actions.h"
#include <cmath>
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

void launch_app(Trip &trip) {
  std::cout << "Choose options:\n";
  std::cout << "1. Add new trip. (Type '1')\n";
  std::cout << "2. Load trip. (Type '2')\n";
  std::cout << "3. Exit. (Type '3')\n";
  int input =
      numerical_input("Invalid input.  Try again (Type 1, 2 or 3): ", 1, 3);
  system("clear");
  switch (input) {
  case 1:
    add_new_trip(trip);
    break;
  case 2:
    load_history(trip);
  default:
    exit(0);
    break;
  }
}

void add_new_trip(Trip &trip) {
  std::cout << "\nNew trip:\n";
  std::cout << "\nEnter the name of your trip:\n";
  std::string trip_name;
  std::cin.ignore();
  std::getline(std::cin, trip_name);
  trip = Trip(trip_name);
  std::cin.clear();
  interface(trip);
}

void interface(Trip &trip) {
  system("clear");
  std::cout << "Choose option:\n";
  std::cout << "1. Add new participant. (Type '1')\n";
  std::cout << "2. Add transaction. (Type '2')\n";
  std::cout << "3. Show people. (Type '3')\n";
  std::cout << "4. Show transaction history. (Type '4')\n";
  std::cout << "5. Show settlement. (Type '5')\n";
  std::cout << "6. Exit. (Type '6')\n";
  int input = numerical_input(
      "Invalid input.  Try again (Type number from 1 to 6): ", 1, 6);
  system("clear");
  switch (input) {
  case 1:
    add_participant(trip);
    break;
  case 2:
    add_transactions_menu(trip);
    break;
  case 3:
    show_people(trip);
    break;
  case 4:
    show_trans(trip);
    interface(trip);
    break;
  case 5:
    settle(trip);
    break;
  default:
    exit_app(trip);
    break;
  }
}

// exit and save trip to file
void exit_app(Trip &trip) {
  // creates input to event choice file
  std::string saveline = trip.get_name() + "&./." + trip.get_name() + ".txt";
  std::ifstream trips;
  std::ofstream otrips;
  std::string line;
  bool file_new = true;
  trips.open("./.trips.txt");
  getline(trips, line);
  getline(trips, line);
  // checks if the trip already exists
  while (line != "") {
    if (line == saveline)
      file_new = false;
    getline(trips, line);
  }
  trips.close();
  // appends a path if the trip is new
  if (file_new) {
    otrips.open("./.trips.txt", std::ios::app);
    otrips << saveline << '\n';
    otrips.close();
  }
  // saves trip info to an unique file
  otrips.open("./." + trip.get_name() + ".txt", std::ios::trunc);
  trip.save_to_file(otrips);
  otrips.close();
  exit(0);
}

void load_history(Trip &curr_trip) {
  std::cout << "\nChoose trip:\n";
  std::ifstream trpfile;
  std::string line;
  std::pair<std::string, std::string> trip_inf;
  std::vector<std::pair<std::string, std::string>> tripsvect;
  trpfile.open("./.trips.txt");
  getline(trpfile, line);
  // Shows info if there are no trips saved
  if (line == "") {
    std::cout << "No trips found :(\n\n";
    launch_app(curr_trip);
  } else
    // Loading info about existing trips into vector
    while (line != "") {
      bool amp = false;
      for (const char &c : line)
        if (!amp) {
          if (c == '&') {
            amp = true;
            continue;
          }
          trip_inf.first += c;
        } else
          trip_inf.second += c;
      tripsvect.push_back(trip_inf);
      trip_inf.first = std::string();
      trip_inf.second = std::string();
      getline(trpfile, line);
    }
  trpfile.close();
  int i = 0;
  // shows trip to choose
  for (const std::pair<std::string, std::string> &pa : tripsvect)
    std::cout << i++ + 1 << ") " << pa.first << "\n";
  int input = 0;
  input = numerical_input("Invalid input.", 1, i);
  trpfile.open(tripsvect.at(input - 1).second);
  // loading chosen trip
  curr_trip = Trip(tripsvect.at(input - 1).first, trpfile);
  trpfile.close();
  std::cout << "Trip loaded succesfully!\n";
  interface(curr_trip);
}

void add_participant(Trip &trip_to_init) {
  std::cout << "\nAdd participant:\n";
  std::cout << "\nEnter the name of new participant:\n";
  std::string name;
  // unique IDs
  unsigned int id = trip_to_init.get_people_size() + 1;
  std::cin >> name;
  Person person_to_add(id, name);
  trip_to_init.add_person(person_to_add);
  std::cout << "Do you want to change participant's attributes? [Y/N]\n";
  std::cout << trip_to_init.get_person(id - 1).print_atts();
  if (is_input_positive())
    set_attributes(trip_to_init, id);
  else
    interface(trip_to_init);
}

void show_people(Trip &trip) {
  trip.print_people(std::cout);
  press_to_continue();
  interface(trip);
}

void show_trans(Trip &trip) {
  trip.print_trans(std::cout);
  press_to_continue();
  interface(trip);
}

// check if user input is a number in given range
template <typename T> T numerical_input(std::string message, T min, T max) {
  std::string input;
  T input_val = 0;
  while (true) {
    try {
      std::cin >> input;
      input_val = std::stoi(input);
      if (input_val >= min && input_val <= max)
        break;
    } catch (...) {
    }
    std::cout << message;
  }
  return input_val;
}

// check if float input is a number in given range
template <> float numerical_input(std::string message, float min, float max) {
  std::string input;
  float input_val = 0;
  while (true) {
    try {
      std::cin >> input;
      input_val = std::stof(input);
      if (input_val >= min && input_val <= max)
        break;
    } catch (...) {
    }
    std::cout << message;
  }
  return input_val;
}

// set selected attribute to opposite value
void set_attributes(Trip &trip_to_init, int person_id) {
  system("clear");
  std::cout
      << "What attribute do you want to change? Type number as an input\n";
  std::cout << trip_to_init.get_person(person_id - 1).print_atts();
  int input = numerical_input(
      "Invalid input.  Try again (Type nuber from 1 to 7): ", 1, 7);
  Person::Category category = static_cast<Person::Category>(input - 1);
  trip_to_init.get_person(person_id - 1).set_att(category);
  system("clear");
  std::cout << "AFTER CHANGE:\n"
            << trip_to_init.get_person(person_id - 1).print_atts();
  std::cout << "Do you want to change anything else? [Y/N] \n";
  if (is_input_positive())
    set_attributes(trip_to_init, person_id);
  else
    interface(trip_to_init);
}

// select collective or specific transaction
void add_transactions_menu(Trip &trip) {
  system("clear");
  if (!trip.get_people_size()) {
    std::cout << "\nAdd people before adding transactions";
    press_to_continue();
    interface(trip);
    return;
  }
  std::cout << "\nAdd transactions:\n";
  std::cout << "Choose options:\n";
  std::cout << "1. Add collective transaction(all participants included).(Type "
               "'1')\n";
  std::cout << "2. Add specific transaction with limited number of "
               "participants.(Type '2')\n";
  int input =
      numerical_input("Invalid input.  Try again (Type 1 or 2): ", 1, 2);
  if (input == 1)
    add_transaction(trip, false);
  else
    add_transaction(trip, true);

  interface(trip);
}

std::string print_categories() {
  std::string output;
  for (int i = 0; i <= 6; i++) {
    Person::Category cat = static_cast<Person::Category>(i);
    output += std::to_string(i + 1) + ". " + Person::Cat_to_str(cat) + "\n";
  }
  return output;
}

// add specific r collective transaction
void add_transaction(Trip &trip, bool is_specific) {
  system("clear");
  std::cout << "\nAdd collective transaction:\n";
  std::cout << "Select payer id: \n ";
  trip.print_people(std::cout);
  int size = trip.get_people_size();
  std::string message = "Invalid input.  Try again (Type number from 1 to " +
                        std::to_string(size) + "): ";
  int payer_id = numerical_input(message, 1, size);
  std::cout << "\nType the category number:\n";
  std::cout << print_categories();
  int category_number = numerical_input(
      "Invalid input.  Try again (Type number from 1 to 7): ", 1, 7);
  Person::Category category =
      static_cast<Person::Category>(category_number - 1);
  std::cout << "\nPlease enter payed amount\n";
  float money = numerical_input(
      "Invalid input.  Try again (Type a positive amount greater than 0.01): ",
      0.01f, 9999999.0f);
  if (is_specific) {
    std::vector<int> included_ids =
        get_included(message, size); // vector of included participants
    std::shared_ptr<Transaction> transaction =
        std::make_shared<SpecificTransaction>(money, payer_id, category,
                                              included_ids);
    trip.add_transaction(transaction);
    std::cout << "\nTransaction added\n";
    press_to_continue();
  } else {
    try {
      std::shared_ptr<Transaction> transaction =
          std::make_shared<CollectiveTransaction>(money, payer_id, category);
      trip.add_transaction(transaction);
      std::cout << "\nTransaction added\n";
      press_to_continue();
    } catch (my_excetpions) {
      std::cout << "\nNone of the people is included in that category, please "
                   "try again";
      press_to_continue();
      add_transaction(trip, is_specific);
    }
  }
}

// get from user people included in the transaction
std::vector<int> get_included(std::string message, int size) {
  std::vector<int> included_ids; // vector of included participants
  bool flag = true;
  while (flag == true) {
    std::cout << "Add a participant in current transaction (type one's ID)\n";
    int person_id = numerical_input(message, 1, size);
    int person_id_cast = person_id;
    while (std::find(included_ids.begin(), included_ids.end(),
                     person_id_cast) != included_ids.end()) {
      // Checking whether certain ID has already been added
      std::cout << "This person has already been included (Type ID of another "
                   "person)\n";
      std::cin.clear();
      int person_id = numerical_input(message, 1, size);
      person_id_cast = person_id;
      std::cin.clear();
    }
    included_ids.push_back(person_id_cast);
    if (included_ids.size() != size) {
      std::cout << "Do you want to add another person? [Y/N]\n";
      flag = is_input_positive();
    } else {
      std::cout << "No more participants to add";
      break;
    }
  }
  return included_ids;
}

void settle(Trip &trip) {
  std::cout << "Settlement Transfers:\n\n";
  // calculating wanted settlements
  std::map<std::pair<int, int>, float> trans_map = trip.calc_transfers();
  std::pair<int, std::pair<int, int>> *ids =
      new std::pair<int, std::pair<int, int>>[trans_map.size()];
  // nothing to settle case
  if (trans_map.size() == 0) {
    std::cout << "Everybody even!\n\n";
    press_to_continue();
    interface(trip);
  }
  int i = 0;
  // printing settlement transactions
  for (const std::pair<std::pair<int, int>, float> &pa : trans_map) {
    std::pair<int, std::pair<int, int>> id;
    std::cout << i + 1 << ". ";
    std::cout << "[" << trip.get_person(pa.first.first - 1).get_name()
              << " -> ";
    std::cout << trip.get_person(pa.first.second - 1).get_name() << "]: ";
    float rounded_money = round(pa.second * 100.0f) / 100.0f;
    std::cout << rounded_money << '\n';
    id.first = i;
    id.second = pa.first;
    *(ids + i) = id;
    i++;
  }
  std::cout << '\n';
  // option to immidiately settle
  std::cout << "Would you like to settle any debt? [Y or N]\n";
  if (is_input_positive()) {
    std::cout << "Which debt do you want to settle? [insert debt number or 0 "
                 "to exit]\n";
    int input = numerical_input("Invalid input, try again! ", 0, i + 1);
    if (input == 0) {
      delete[] ids;
      return interface(trip);
    } else {
      SpecificTransaction trans(
          trans_map[ids[input - 1].second], ids[input - 1].second.first,
          Person::Category::other, {ids[input - 1].second.second});
      std::shared_ptr<Transaction> tptr =
          std::make_shared<SpecificTransaction>(trans);
      trip.add_transaction(tptr);
      std::cout << "Settled!\n";
    }
  }
  delete[] ids;
  interface(trip);
}

// helper function to close displayed info
void press_to_continue() {
  std::cout << "\nPress Enter to continue...";
  std::cin.ignore(10, '\n');
  std::cin.get();
}

// checks if input is valid and returns value of the input
bool is_input_positive() {
  std::string input;
  while (true) {
    std::cin >> input;
    for (auto &c : input)
      c = toupper(c);
    if (input == "N" || input == "NO" || input == "Y" || input == "YES")
      break;
    std::cout << "Invalid input. (enter Y or N): ";
  }
  return (input == "Y" || input == "YES");
}