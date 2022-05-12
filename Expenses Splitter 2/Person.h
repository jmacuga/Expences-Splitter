#pragma once

#include <string>
using namespace std;

class Person
{
	unsigned int id;
	string name;
	bool alcohol;
	bool nicotine;
	bool gluten;
	bool meat;
	bool dairy;
	//balance - sum of money to return/receive
	double balance;
public:
	Person(unsigned int pid, string nm, bool alc = true, bool nict = true,
		   bool glut = true, bool me = true, bool di = true):
	id(pid), name(nm), alcohol(alc), nicotine(nict), gluten(glut), meat(me), dairy(di)
	{balance = 0.0;};
	string get_name();
	double get_balance();
};
