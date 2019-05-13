#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
#include "Console.h"
#include "Logic.h"
using namespace std;

class Account
{
protected:
	string login;
	string pin;
	const string expansion = ".txt";
	string secret_answer;
	const string history_operation = "HistoryOperation";
public:
	Account();
	~Account();

	friend istream& operator>>(istream& in, Account& Account);
	bool input();
	void forgot_password();
	int account_in_bank(int page);
	void settings(int selection);
	void operation(int selection);
	void advanced_search(vector<string>advanced_search_operation);
	//friend ostream& operator<<(ostream& out, Account& Account);	
};