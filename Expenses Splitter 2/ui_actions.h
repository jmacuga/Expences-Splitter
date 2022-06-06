#pragma once
#include "Trip.h"

void launch_app(Trip& Trip);
void add_new_trip(Trip& trip);
void interface(Trip &trip);
void show_people(Trip& trip);
void show_trans(Trip& trip);
void load_history(Trip &curr_trip);
void add_participant(Trip &trip_to_init);
void add_transactions_menu(Trip& trip);
void add_transaction(Trip& trip, bool is_specific = false);
void settle(Trip& trip);
void exit_app(Trip& trip);
void set_attributes(Trip& trip_to_init, int person_id);
void press_to_continue();
template<typename T>
T numerical_input(std::string message, T min, T max);
std::vector<int> get_included(std::string message, int size);
bool is_input_positive();