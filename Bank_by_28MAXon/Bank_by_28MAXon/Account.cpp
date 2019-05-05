#include "pch.h"
#include "Account.h"
#include "Console.h"

Account::Account()
{
	pin = "Нет данных";
	login = "Нет данных";
	expansion = ".txt";
	secret_answer = "Нет данных";
}

Account::~Account()
{

};

istream& operator>>(istream& in, Account& Account)
{
	Console interface_page;
	interface_page.set_cursor_local(25, 3);
	in >> Account.login;

	interface_page.set_cursor_local(25, 6);
	in >> Account.pin;

	return in;
}

bool Account::input()
{
	string name_of_file;
	name_of_file = login + expansion;
	ifstream file(name_of_file);
	if (!file.is_open() )
	{
		return false;
	}
	else
	{
		char password [20];
		int i = 0;
		while(!file.eof())
		{
			file.getline(password, 20);
			if (i == 1)
			{
				if (password == pin)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (i > 1)
			{
				break;
			}
			i++;
		}
		file.close();
	}
}

void Account::forgot_password()
{

}

int Account::account_in_bank(int page)
{
	Console work_interface;
	switch (page)
	{
		case 1:
		{
			work_interface.interface_menu_main_page();
			string data[12];
			ifstream file_data(login + expansion);
			for (int i = 0; i < 12; i++)
			{
				file_data >> data[i];
			}
			work_interface.set_cursor_local(54, 10);
			cout << data[11] << " RUB" << endl << endl;
			work_interface.set_cursor_local(52, 26);
			int choise;
			cin >> choise;
			if (choise == 1)
			{
				work_interface.set_cursor_local(21, 26);
				cin >> choise;
				settings(choise);
				return 1;
			}
			else
			{
				work_interface.set_cursor_local(102, 26);
				cin >> choise;
				return choise;
			}
			break;
		}
		case 2:
		{
			work_interface.interface_operation();
			work_interface.set_cursor_local(52, 29);
			int choise;
			cin >> choise;
			if (choise == 1)
			{
				work_interface.set_cursor_local(21, 29);
				cin >> choise;
				operation(choise);
				return 2;
			}
			else
			{
				work_interface.set_cursor_local(102, 29);
				cin >> choise;
				return choise;
			}
			break;
		}
		case 3:
		{

		}
	}
}

void Account::settings(int selection)
{
	system("cls");
	Console interface_myData;
	switch (selection)
	{
	case 1:
	{
		interface_myData.interface_myData();
		string Data[12];
		ifstream file_Data(login + expansion);
		int y = 0;
		for (int i = 0; i < 12; i++)
		{
			file_Data >> Data[i];
			interface_myData.set_cursor_local(28, 3 + y);
			if (i < 11)
			{
				cout << Data[i];
			}
			y = y + 3;
		}
		file_Data.close();
		int choise;
		interface_myData.set_cursor_local(1, 38);
		cout << "Ваш выбор: ";
		cin >> choise;
		if (choise == 0)
		{
			break;
		}
		else
		{
			interface_myData.set_cursor_local(28, 3 * choise);
			cout << "                      ";
			interface_myData.set_cursor_local(28, 3 * choise);
			cin >> Data[choise - 1];
			ofstream file_rewrite_Data(login + expansion, ios_base::out);
			y = 0;
			for (int i = 0; i < 12; i++)
			{
				interface_myData.set_cursor_local(28, 3 + y);
				if (i < 11)
				{
					cout << Data[i];
					file_rewrite_Data << Data[i] << endl;
				}
				else
				{
					file_rewrite_Data << Data[i];
				}
			}
			file_rewrite_Data.close();
			system("pause");
		}
	}
	}
}

void Account::operation(int selection)
{
	system("cls");
	
	switch (selection)
	{
	case 1:
	{

	}
	}
}