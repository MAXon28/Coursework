#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
#include "Console.h"
#include "Logic.h"
#include "stdlib.h"
using namespace std;

class Account
{
protected:
	string login;
	string pin;
	const string Theme = "Theme";
	const string expansion = ".txt";
	const string history_operation = "HistoryOperation";
	const string deposit = "Deposit";
	const string credit = "Credit";
public:
	Account();
	~Account();
	friend istream& operator>>(istream& in, Account& Account);
	bool input();
	int account_in_bank(int page);
	void check_return_cash();
	void check_return_credit();
	void settings(int selection);
	void operation(int selection);
	void advanced_search(vector<string>advanced_search_operation);
	int get_number_Theme();
};