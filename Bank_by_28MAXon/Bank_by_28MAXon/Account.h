#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
#include <time.h>
#include "conio.h"
#include "stdio.h"
#include "Console.h"
#include "Logic.h"
using namespace std;

class Account
{
protected:
	string login;
	string pin;
	string expansion;
	string secret_answer;
	string history_operation;
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