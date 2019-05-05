#pragma once
#include <iostream>
#include <string>
#include "Account.h"

class Registration : public Account
{
private:
	string name;
	string surname;
	int age;
	unsigned long long int number_of_phone;
	string email_adress;
	string country;
	string city;
	unsigned long long int number_of_card;
public:
	Registration();
	~Registration();

	friend istream& operator>>(istream& in, Registration& registr);
	bool confirmation();
};