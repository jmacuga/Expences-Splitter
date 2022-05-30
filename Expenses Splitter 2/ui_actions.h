#pragma once
#include "Trip.h"

void launch_app(Trip& Trip);
void add_new_trip(Trip& trip);
void interface(Trip &trip);
void load_history(Trip &curr_trip);
// void add_participants(Trip &trip_to_init);
void add_participant(Trip &trip_to_init);
void add_transactions(Trip &trip_to_init);
void add_singular_transaction();

void add_collective_transaction(Trip &trip_to_init);
void add_specific_transaction(Trip &trip_to_init);