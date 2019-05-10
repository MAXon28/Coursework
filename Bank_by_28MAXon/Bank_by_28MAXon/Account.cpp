#include "pch.h"
#include "Account.h"

Account::Account()
{
	pin = "Нет данных";
	login = "Нет данных";
	expansion = ".txt";
	secret_answer = "Нет данных";
	history_operation = "HistoryOperation";
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
					work_interface.set_cursor_local(10, 7 + j + k);
					cout << history_bank[count_operation];
					if (i == 3)
					{
						work_interface.set_cursor_local(19, 7 + j + k);
						cout << "RUB";
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
					Logic logic_search;
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
								work_interface.set_cursor_local(10, 7 + j + k);
								cout << history_bank[count_string];
								if (i == 3)
								{
									work_interface.set_cursor_local(19, 7 + j + k);
									cout << "RUB";
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
	switch (selection)
	{
	case 1:
	{
		interface_operation.interface_operation(1);
		string favourite_film;
		interface_operation.set_cursor_local(80, 1);
		cin >> favourite_film;
		string checking;
		ifstream file_film(login + expansion);
		for (int i = 0; i < 11; i++)
		{
			file_film >> checking;
			if (i == 10)
			{
				if (checking == favourite_film)
				{
					unsigned long int cash;
					file_film >> cash;
					file_film.close();
					interface_operation.set_cursor_local(41, 4);
					cout << cash;
					Logic logic_refill_card;
					interface_operation.set_cursor_local(41, 7);
					cin >> logic_refill_card;
					unsigned long int new_cash;
					new_cash = logic_refill_card.operations(1, cash, false, login);
					interface_operation.set_cursor_local(41, 10);
					cout << new_cash;
					interface_operation.set_cursor_local(1, 13);
					cout << "Подтверждаете операцию? ";
					string confirmation;
					bool print;
					do
					{
						cin >> confirmation;
						if (confirmation == "Да")
						{
							logic_refill_card.operations(1, cash, true, login);
							system("cls");

							SYSTEMTIME st;
							GetLocalTime(&st);
							ofstream file_history(login + history_operation + expansion, ios_base::app);
							file_history << logic_refill_card << endl << st.wDayOfWeek << endl  << st.wDay << " " << st.wMonth << " " << st.wYear << endl  << "ПОПОЛНЕНИЕ БАНКОВСКОЙ КАРТЫ" << endl << "новая операция";
							file_history.close();

							interface_operation.set_cursor_local(34, 15);
							cout << "ЗАЧИСЛЕНО " << logic_refill_card << " RUB НА ВАШУ КАРТУ!";
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
			cout << "Дата выполнения операции(ДД.ММ.ГГГГ):";			
			int number_operation;
			inerface_advanced_search.set_cursor_local(73, 20);
			cin >> number_operation;
			string name_operation;
			name_operation = logic_advanced_search.number_operation_to_name_operation(number_operation);
			string sum_cash;
			inerface_advanced_search.set_cursor_local(73, 21);
			cin >> sum_cash;
			string date_operation;
			inerface_advanced_search.set_cursor_local(95, 22);
			cin >> date_operation;
			advanced_search_operation = logic_advanced_search.advanced_search(advanced_search_operation, name_operation, sum_cash, date_operation);
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
					inerface_advanced_search.set_cursor_local(10, 7 + j + k);
					cout << advanced_search_operation[count_string];
					if (i == 3)
					{
						inerface_advanced_search.set_cursor_local(19, 7 + j + k);
						cout << "RUB";
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
			check_kind = true;
			system("pause");
		}
	} while (check_kind == false);
}