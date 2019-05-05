#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Account.h"
#include <Windows.h>
using namespace std;

class Account
{
protected:
	string login;
	string pin;
	string expansion;
	string secret_answer;
public:
	Account();
	~Account();

	friend istream& operator>>(istream& in, Account& Account);
	bool input();
	void forgot_password();
	int account_in_bank(int page);
	void settings(int selection);
	void operation(int selection);
	friend ostream& operator<<(ostream& out, Account& Account);	
};