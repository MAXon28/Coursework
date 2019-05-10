#include "pch.h"
#include <fstream>
#include "registration.h"
#include "Console.h"
using namespace std;

Registration::Registration()
{
}


Registration::~Registration()
{
}

istream& operator>>(istream& in, Registration& registr)
{
	Console interface_page;
	bool check = false;
	int count;
	do
	{
		count = 0;
		interface_page.set_cursor_local(28, 3);
		in >> registr.name;
		for (int i = 0; i < registr.name.length(); i++)
		{
			if (registr.name[i] < 192 - 256 || registr.name[i] > 256 - 256)
			{
				count++;
			}
		}
		if (count == 0)
		{
			check = true;
			interface_page.set_cursor_local(66, 3);
			cout << "                                   ";
		}
		else
		{
			check = false;
			interface_page.set_cursor_local(66, 3);
			cout << "В данном поле ТОЛЬКО русские буквы!";
		}
	} while (check != true);

	do
	{
		count = 0;
		interface_page.set_cursor_local(28, 6);
		in >> registr.surname;
		for (int i = 0; i < registr.surname.length(); i++)
		{
			if (registr.surname[i] < 192 - 256 || registr.surname[i] > 256 - 256)
			{
				count++;
			}
		}
		if (count == 0)
		{
			check = true;
			interface_page.set_cursor_local(66, 6);
			cout << "                                   ";
		}
		else
		{
			check = false;
			interface_page.set_cursor_local(66, 6);
			cout << "В данном поле ТОЛЬКО русские буквы!";
		}
	} while (check != true);

	interface_page.set_cursor_local(28, 9);
	in >> registr.age;

	interface_page.set_cursor_local(28, 12);
	in >> registr.number_of_phone;

	interface_page.set_cursor_local(28, 15);
	in >> registr.email_adress;

	interface_page.set_cursor_local(28, 18);
	in >> registr.country;

	interface_page.set_cursor_local(28, 21);
	in >> registr.city;

	interface_page.set_cursor_local(28, 24);
	in >> registr.number_of_card;

	check = false;
	do
	{
		interface_page.set_cursor_local(28, 27);
		in >> registr.login;
		ifstream file(registr.login + ".txt");
		if (!file.is_open())
		{
			check = true;
			interface_page.set_cursor_local(66, 27);
			cout << "                            ";
		}
		else
		{
			interface_page.set_cursor_local(66, 27);
			cout << "Данный логин уже существует!";
		}
	} while (check != true);

	interface_page.set_cursor_local(28, 30);
	in >> registr.pin;

	interface_page.set_cursor_local(28, 33);
	in >> registr.secret_answer;

	return in;
}

bool Registration::confirmation()
{
	Console confirm;

	confirm.set_cursor_local(28, 3);
	cout << name;

	confirm.set_cursor_local(28, 6);
	cout << surname;

	confirm.set_cursor_local(28, 9);
	cout << age;

	confirm.set_cursor_local(28, 12);
	cout << number_of_phone;

	confirm.set_cursor_local(28, 15);
	cout << email_adress;

	confirm.set_cursor_local(28, 18);
	cout << country;

	confirm.set_cursor_local(28, 21);
	cout << city;

	confirm.set_cursor_local(28, 24);
	cout << number_of_card;

	confirm.set_cursor_local(28, 27);
	cout << login;

	confirm.set_cursor_local(28, 30);
	cout << pin;

	confirm.set_cursor_local(28, 33);
	cout << secret_answer;

	confirm.set_cursor_local(12, 42);
	int choice_confirm;
	cin >> choice_confirm;
	if (choice_confirm == 1)
	{
		string name_file;
		name_file = login + expansion;
		ofstream file_nick(name_file);
		file_nick << login << endl << pin << endl << name << endl << surname << endl << age << endl << number_of_phone << endl << email_adress << endl << country << endl << city << endl << number_of_card << endl << secret_answer << endl << "128";
		file_nick.close();
		system("cls");
		confirm.set_cursor_local(1, 0);
		cout << "Регистрация проведена успешно! Спасибо, что выбрали нас!" << endl;
		return true;
	}
	else
	{
		return false;
	}
}