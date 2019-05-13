#include "pch.h"
#include "Account.h"

Account::Account()
{
	pin = "Нет данных";
	login = "Нет данных";
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
			work_interface.interface_main_page();
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
			work_interface.interface_operations_page();
			int choise;
			work_interface.set_cursor_local(52, 29);
			cin >> choise;
			if (choise == 1)
			{
				work_interface.set_cursor_local(17, 29);
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
			// Страничка с историями банковских операций
			Logic logic_search;
			work_interface.interface_history_page();
			vector <string> history_bank; // сюда буду закидывать все данные из файла, а потом сортировать в случае надобности
			ifstream file_history(login + history_operation + expansion);
			string line;
			while (!file_history.eof())
			{
				getline(file_history, line);
				history_bank.push_back(line);
			}
			file_history.close();
			int count_operation = history_bank.size() - 1;
			int k = 0; // Для курсора
			int j = 0; // Для курсора

			// Вывожу все банковские операции, которые происходили у пользователя
			do
			{
				if (history_bank[count_operation] == "новая операция")
				{
					count_operation--;
				}
				int i = 0; // Для курсора
				while (history_bank[count_operation] != "новая операция")
				{
					if (i == 2)
					{
						work_interface.set_cursor_local(10, 7 + j + k);
						cout << logic_search.number_day_to_name_day(history_bank[count_operation]);
					}
					else if (i == 3)
					{
						work_interface.set_cursor_local(10, 7 + j + k);
						cout << history_bank[count_operation];
						work_interface.set_cursor_local(19, 7 + j + k);
						cout << "RUB";
					}
					else if (i >= 4)
					{
						history_bank[count_operation].pop_back();
						i--;
						j--;
					}
					else
					{
						work_interface.set_cursor_local(10, 7 + j + k);
						cout << history_bank[count_operation];
					}
					j++;
					count_operation--;
					if (count_operation < 0)
					{
						break;
					}
					i++;
				}
				k = k + 2;
			} while (count_operation >= 0);

			bool check;
			int choise;
			do
			{
				work_interface.set_cursor_local(68, 8);
				cin >> choise;
				if (choise == 1)
				{					
					int number_operation;
					work_interface.set_cursor_local(64, 14);
					cin >> number_operation;
					string name_operation;
					name_operation = logic_search.number_operation_to_name_operation(number_operation); // Перевожу номер операции в соответствующее название банковской операции
					if (name_operation == "0")
					{
						advanced_search(history_bank); // Расширенный поиск
					}
					else
					{
						history_bank = logic_search.normal_search(history_bank, name_operation); // Логика обычного поиска 
						int count_string = history_bank.size() - 1;
						k = 0;
						j = 0;
						for (int i = 0; i < 6; i++)
						{
							for (int n = 0; n < 4; n++)
							{
								work_interface.set_cursor_local(10, 7 + j + k);
								cout << "                            "; // Очищаю всю таблицу для обновления
								j++;
							}
							k = k + 2;
						}
						k = 0;
						j = 0;
						do
						{
							if (history_bank[count_string] == "новая операция")
							{
								count_string--;
							}
							int i = 0;
							while (history_bank[count_string] != "новая операция")
							{
								if (i == 2)
								{
									work_interface.set_cursor_local(10, 7 + j + k);
									cout << logic_search.number_day_to_name_day(history_bank[count_string]);
								}
								else if (i == 3)
								{
									work_interface.set_cursor_local(10, 7 + j + k);
									cout << history_bank[count_string];
									work_interface.set_cursor_local(19, 7 + j + k);
									cout << "RUB";
								}
								else if (i >= 4)
								{
									history_bank[count_string].pop_back();
									i--;
									j--;
								}
								else
								{
									work_interface.set_cursor_local(10, 7 + j + k);
									cout << history_bank[count_string];
								}
								j++;
								count_string--;
								if (count_string < 0)
								{
									break;
								}
								i++;
							}
							k = k + 2;
						} while (count_string >= 0);
					}
					check = true;
					work_interface.set_cursor_local(1, 43);
					system("pause");
					return 3;
				}
				else if (choise == 2)
				{
					// меню
					work_interface.set_cursor_local(78, 41);
					cin >> choise;
					check = true;
					return choise;
				}
				else
				{
					check = false;
				}
			} while (check == false);
			break;
		}
		case 4:
		{
			return 0;
			break;
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
			if (i < 10)
			{
				cout << Data[i];
			}
			else if (i == 10)
			{
				cout << "****";
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
			if (choise == 1)
			{
				bool check = false;
				string file_rename = Data[choise - 1] + expansion;
				do
				{
					interface_myData.set_cursor_local(28, 3 * choise);
					cin >> Data[choise - 1];
					ifstream file(Data[choise - 1] + expansion);
					if (!file.is_open())
					{
						check = true;
						login = Data[choise - 1];
						interface_myData.set_cursor_local(71, 3 * choise);
						cout << "                            ";
					}
					else
					{
						interface_myData.set_cursor_local(71, 3 * choise);
						cout << "Данный логин уже существует!";
					}
				} while (check != true);
			}
			else
			{
				cin >> Data[choise - 1];
			}
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
	Console interface_operation;
	Logic logic_refill_card;
	unsigned long int cash, new_cash;
	string favourite_film, checking;
	string confirmation;
	switch (selection)
	{
	case 1:
	{
		interface_operation.interface_operation(1);
		interface_operation.set_cursor_local(80, 1);
		cin >> favourite_film;
		ifstream file_film(login + expansion);
		for (int i = 0; i < 11; i++)
		{
			file_film >> checking;
			if (i == 10)
			{
				if (checking == favourite_film)
				{
					file_film >> cash;
					file_film.close();
					interface_operation.set_cursor_local(41, 4);
					cout << cash;
					interface_operation.set_cursor_local(41, 7);
					cin >> logic_refill_card;
					new_cash = logic_refill_card.operations(1, cash, false, login);
					interface_operation.set_cursor_local(41, 10);
					cout << new_cash;
					interface_operation.set_cursor_local(1, 13);
					cout << "Подтверждаете операцию? ";
					bool print;
					do
					{
						cin >> confirmation;
						if (confirmation == "Да")
						{
							logic_refill_card.operations(1, cash, true, login);
							system("cls");

							SYSTEMTIME stime;
							GetLocalTime(&stime);
							ifstream file_history(login + history_operation + expansion);
							if (!file_history.eof())
							{
								file_history.close();
								ofstream file_history(login + history_operation + expansion, ios_base::app);
								file_history << endl << logic_refill_card << endl << stime.wDayOfWeek << endl << stime.wDay << " " << stime.wMonth << " " << stime.wYear << endl << "ПОПОЛНЕНИЕ БАНКОВСКОЙ КАРТЫ" << endl << "новая операция";
							}
							else
							{
								ofstream file_history(login + history_operation + expansion, ios_base::app);
								file_history << logic_refill_card << endl << stime.wDayOfWeek << endl << stime.wDay << " " << stime.wMonth << " " << stime.wYear << endl << "ПОПОЛНЕНИЕ БАНКОВСКОЙ КАРТЫ" << endl << "новая операция";
							}
							file_history.close();

							interface_operation.set_cursor_local(34, 15);
							cout << "ЗАЧИСЛЕНО " << logic_refill_card << " RUB НА ВАШУ КАРТУ!" << endl;;
							system("pause");
							print = true;
						}
						else if (confirmation == "Нет")
						{
							print = true;
							break;
						}
					} while (print != true);
					break;
				}
				else
				{
					interface_operation.set_cursor_local(34, 15);
					cout << "НЕПРАВИЛЬНЫЙ ОТВЕТ НА ВОПРОС!";
					interface_operation.set_cursor_local(4, 16);
					cout << "В целях безопасности банк не может провести операцию, пока вы не дадите правильный ответ на вопрос!";
					break;
				}
			}
		}
		file_film.close();
	}
	case 2:
	{
		break;
	}
	case 3:
	{
		break;
	}
	case 4:
	{
		break;
	}
	case 5:
	{
		interface_operation.interface_operation(5);
		unsigned long int all_return;
		interface_operation.set_cursor_local(80, 1);
		cin >> favourite_film;
		ifstream file_film(login + expansion);
		for (int i = 0; i < 11; i++)
		{
			file_film >> checking;
			if (i == 10)
			{
				if (checking == favourite_film)
				{
					interface_operation.set_cursor_local(1, 38);
					cout << "Выберите номер вклада: ";
					string number_of_deposit;
					cin >> number_of_deposit;
					interface_operation.interface_local_operation();
					file_film >> cash;
					interface_operation.set_cursor_local(47, 3);
					cout << cash;
					if (number_of_deposit == "1")
					{
						Logic logic_deposit(30, 1095);
						interface_operation.set_cursor_local(47, 6);
						cin >> logic_deposit;
						logic_refill_card = logic_deposit;
						new_cash = logic_deposit.operations(5, cash, false, login);
						interface_operation.set_cursor_local(47, 9);
						cout << new_cash;
						unsigned long int percent_cash = logic_deposit.amount_of_income();
						interface_operation.set_cursor_local(47, 12);
						cout << percent_cash;
						all_return = logic_deposit.amount_all_return();
						interface_operation.set_cursor_local(47, 15);
						cout << all_return;
					}
					if (number_of_deposit == "2")
					{
						Logic logic_deposit(10, 182);
						interface_operation.set_cursor_local(47, 6);
						cin >> logic_deposit;
						logic_refill_card = logic_deposit;
						new_cash = logic_deposit.operations(5, cash, false, login);
						interface_operation.set_cursor_local(47, 9);
						cout << new_cash;
						unsigned long int percent_cash = logic_deposit.amount_of_income();
						interface_operation.set_cursor_local(47, 12);
						cout << percent_cash;
						all_return = logic_deposit.amount_all_return();
						interface_operation.set_cursor_local(47, 15);
						cout << all_return;
					}
					if (number_of_deposit == "3")
					{
						Logic logic_deposit(5, 365);
						interface_operation.set_cursor_local(47, 6);
						cin >> logic_deposit;
						logic_refill_card = logic_deposit;
						new_cash = logic_deposit.operations(5, cash, false, login);
						interface_operation.set_cursor_local(47, 9);
						cout << new_cash;
						unsigned long int percent_cash = logic_deposit.amount_of_income();
						interface_operation.set_cursor_local(47, 12);
						cout << percent_cash;
						all_return = logic_deposit.amount_all_return();
						interface_operation.set_cursor_local(47, 15);
						cout << all_return;
					}
				}
				else
				{
					system("cls");
					interface_operation.set_cursor_local(34, 15);
					cout << "НЕПРАВИЛЬНЫЙ ОТВЕТ НА ВОПРОС!";
					interface_operation.set_cursor_local(4, 16);
					cout << "В целях безопасности банк не может провести операцию, пока вы не дадите правильный ответ на вопрос!";
					break;
				}
			}
		}
		file_film.close();
		interface_operation.set_cursor_local(1, 19);
		cout << "Подтверждаете операцию? ";
		bool print;
		do
		{
			cin >> confirmation;
			if (confirmation == "Да")
			{
				logic_refill_card.operations(5, new_cash, true, login);
				system("cls");

				SYSTEMTIME stime_deposit;
				GetLocalTime(&stime_deposit);
				ifstream file_history(login + history_operation + expansion);
				if (!file_history.eof())
				{
					file_history.close();
					ofstream file_history(login + history_operation + expansion, ios_base::app);
					file_history << endl << all_return << endl << logic_refill_card << endl << stime_deposit.wDayOfWeek << endl << stime_deposit.wDay << " " << stime_deposit.wMonth << " " << stime_deposit.wYear << endl << "ОТКРЫТИЕ ВКЛАДА" << endl << "новая операция";
				}
				else
				{
					ofstream file_history(login + history_operation + expansion, ios_base::app);
					file_history << all_return << endl << logic_refill_card << endl << stime_deposit.wDayOfWeek << endl << stime_deposit.wDay << " " << stime_deposit.wMonth << " " << stime_deposit.wYear << endl << "ОТКРЫТИЕ ВКЛАДА" << endl << "новая операция";
				}
				file_history.close();

				interface_operation.set_cursor_local(34, 15);
				cout << "ВКЛАД ОТКРЫТ!";
				print = true;
			}
			else if (confirmation == "Нет")
			{
				print = true;
				break;
			}
		} while (print != true);
		system("pause");
		break;
	}
	case 6:
	{
		break;
	}
	case 7:
	{
		break;
	}
	}
}

void Account::advanced_search(vector<string>advanced_search_operation)
{
	Console inerface_advanced_search;
	Logic logic_advanced_search;
	inerface_advanced_search.set_cursor_local(57, 15);
	cout << "Расширенный поиск (выберите род операции)";
	inerface_advanced_search.set_cursor_local(57, 16);
	cout << "1 - операции со своими счетами";
	inerface_advanced_search.set_cursor_local(57, 17);
	cout << "2 - другому человек";
	inerface_advanced_search.set_cursor_local(57, 18);
	cout << "3 - оплата сотовой связи";
	inerface_advanced_search.set_cursor_local(57, 19);
	cout << "Ваш выбор:";
	string kind;
	bool check_kind;
	string name_operation, sum_cash, day_operation;
	do
	{
		inerface_advanced_search.set_cursor_local(68, 19);
		cin >> kind;
		if (kind == "1")
		{
			inerface_advanced_search.set_cursor_local(57, 20);
			cout << "Номер операции:";
			inerface_advanced_search.set_cursor_local(57, 21);
			cout << "Денежная сумма:";
			inerface_advanced_search.set_cursor_local(57, 22);
			cout << "Номер дня недели:";			
			int number_operation;
			inerface_advanced_search.set_cursor_local(73, 20);
			cin >> number_operation;
			name_operation = logic_advanced_search.number_operation_to_name_operation(number_operation);
			inerface_advanced_search.set_cursor_local(73, 21);
			cin >> sum_cash;
			inerface_advanced_search.set_cursor_local(75, 22);
			cin >> day_operation;
			check_kind = true;
			advanced_search_operation = logic_advanced_search.advanced_search(advanced_search_operation, name_operation, sum_cash, day_operation);
		}
	} while (check_kind == false);
	int count_string = advanced_search_operation.size() - 1;
	int k = 0;
	int j = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int n = 0; n < 4; n++)
		{
			inerface_advanced_search.set_cursor_local(10, 7 + j + k);
			cout << "                            "; // Очищаю всю таблицу для обновления
			j++;
		}
		k = k + 2;
	}
	k = 0;
	j = 0;
	do
	{
		if (advanced_search_operation[count_string] == "новая операция")
		{
			count_string--;
		}
		int i = 0;
		while (advanced_search_operation[count_string] != "новая операция")
		{
			if (i == 2)
			{
				inerface_advanced_search.set_cursor_local(10, 7 + j + k);
				cout << logic_advanced_search.number_day_to_name_day(advanced_search_operation[count_string]);
			}
			else if (i == 3)
			{
				inerface_advanced_search.set_cursor_local(10, 7 + j + k);
				cout << advanced_search_operation[count_string];
				inerface_advanced_search.set_cursor_local(19, 7 + j + k);
				cout << "RUB";
			}
			else if (i >= 4)
			{
				advanced_search_operation[count_string].pop_back();
				i--;
				j--;
			}
			else
			{
				inerface_advanced_search.set_cursor_local(10, 7 + j + k);
				cout << advanced_search_operation[count_string];
			}
			j++;
			count_string--;
			if (count_string < 0)
			{
				break;
			}
			i++;
		}
		k = k + 2;
	} while (count_string >= 0);
}