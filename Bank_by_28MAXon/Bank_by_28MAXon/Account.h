#pragma once
#include <string>
using namespace std;
class account
{
protected:
	string login;
	string pin;
public:
	account();
	~account();
	void input();
	void forgot_password();
		
};

class registration : public account
{
private:
	string name;
	string surname;
	int age;
	int number_of_phone;
	string email_adress;
	string country;
	string city;
	int number_of_card;
public:
	void registr();
};