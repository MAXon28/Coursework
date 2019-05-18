#include "pch.h"
#include "Account.h"

Account::Account()
{
	pin = "Нет данных";
	login = "Нет данных";
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

int Account::account_in_bank(int page)
{
	Console work_interface;
	switch (page)
	{
		case 1:
		{
			// Главная страница
			ifstream file_deposits(login + deposit + expansion);
			if (file_deposits.is_open())
			{
				check_return_cash();
				file_deposits.close();
			}
			ifstream file_credit(login + credit + expansion);
			if (file_credit.is_open())
			{
				check_return_credit();
				file_credit.close();
			}
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
			// Страница с банковскими операциями
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
			// Страница с историями банковских операций
			Logic logic_search;
			work_interface.interface_history_page();
			int X = 10; // Точка курсора по x (будет меняться в зависимости от того, какая операция выводится
			ifstream file_history(login + history_operation + expansion);
			if (!file_history.is_open())
			{
				work_interface.set_cursor_local(7, 9);
				cout << "История пуста!";
			}
			else
			{
				vector <string> history_bank; // сюда буду закидывать все данные из файла, а потом сортировать в случае надобности
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
				int counter_operations = 0;;
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
						if (i == 0 && (history_bank[count_operation] == "ПЕРЕВОД КЛИЕНТУ МаксиБанк" || history_bank[count_operation] == "ПЕРЕВОД КЛИЕНТУ ДРУГОГО БАНКА" || history_bank[count_operation] == "ОПЛАТА СОТОВОЙ СВЯЗИ"))
						{
							X = 15;
							work_interface.set_cursor_local(X, 7 + j + k);
							cout << history_bank[count_operation];
							work_interface.set_cursor_local(2, 8 + j + k);
							cout << history_bank[count_operation - 4];
						}
						else if (i == 2)
						{
							work_interface.set_cursor_local(X, 7 + j + k);
							cout << logic_search.number_day_to_name_day(history_bank[count_operation]);
						}
						else if (i == 3)
						{
							work_interface.set_cursor_local(X, 7 + j + k);
							cout << history_bank[count_operation];
							work_interface.set_cursor_local(X + 9, 7 + j + k);
							cout << "RUB";
						}
						else if (i >= 4)
						{
							if (!(history_bank[count_operation + i] == "ПЕРЕВОД КЛИЕНТУ МаксиБанк" || history_bank[count_operation + i] == "ПЕРЕВОД КЛИЕНТУ ДРУГОГО БАНКА" || history_bank[count_operation + i] == "ОПЛАТА СОТОВОЙ СВЯЗИ"))
							{
								history_bank[count_operation].pop_back();
							}
							i--;
							j--;
						}
						else
						{
							work_interface.set_cursor_local(X, 7 + j + k);
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
					X = 10;
					k = k + 2;
					counter_operations++;
					if (counter_operations == 6)
					{
						work_interface.set_cursor_local(57, 30);
						cout << "Есть ещё операции, которые не отобразились!";
						work_interface.set_cursor_local(57, 31);
						cout << "Используйте поиск!";
					}
				} while (count_operation >= 0 && counter_operations != 6);
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
						work_interface.set_cursor_local(57, 30);
						cout << "                                             ";
						work_interface.set_cursor_local(57, 31);
						cout << "                                             ";
						string name_operation;
						name_operation = logic_search.number_operation_to_name_operation(number_operation); // Перевожу номер операции в соответствующее название банковской операции
						if (name_operation == "0")
						{
							advanced_search(history_bank); // Расширенный поиск
						}
						else
						{
							history_bank = logic_search.normal_search(history_bank, name_operation); // Логика обычного поиска 						
							k = 0;
							j = 0;
							for (int i = 0; i < 6; i++)
							{
								for (int n = 0; n < 4; n++)
								{
									work_interface.set_cursor_local(2, 7 + j + k);
									cout << "                                                  "; // Очищаю всю таблицу для обновления
									j++;
								}
								k = k + 2;
							}
							if (history_bank.size() == 0)
							{
								work_interface.set_cursor_local(3, 9);
								cout << "По Вашему запросу ничего не найдено!";
							}
							else
							{
								int count_string = history_bank.size() - 1;
								k = 0;
								j = 0;
								counter_operations = 0;
								do
								{
									if (history_bank[count_string] == "новая операция")
									{
										count_string--;
									}
									int i = 0;
									while (history_bank[count_string] != "новая операция")
									{
										if (i == 0 && (history_bank[count_string] == "ПЕРЕВОД КЛИЕНТУ МаксиБанк" || history_bank[count_string] == "ПЕРЕВОД КЛИЕНТУ ДРУГОГО БАНКА" || history_bank[count_string] == "ОПЛАТА СОТОВОЙ СВЯЗИ"))
										{
											X = 15;
											work_interface.set_cursor_local(X, 7 + j + k);
											cout << history_bank[count_string];
											work_interface.set_cursor_local(2, 8 + j + k);
											cout << history_bank[count_string - 4];
										}
										else if (i == 2)
										{
											work_interface.set_cursor_local(X, 7 + j + k);
											cout << logic_search.number_day_to_name_day(history_bank[count_string]);
										}
										else if (i == 3)
										{
											work_interface.set_cursor_local(X, 7 + j + k);
											cout << history_bank[count_string];
											work_interface.set_cursor_local(X + 9, 7 + j + k);
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
											work_interface.set_cursor_local(X, 7 + j + k);
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
									X = 10;
									k = k + 2;
									counter_operations++;
									if (counter_operations == 6)
									{
										work_interface.set_cursor_local(57, 30);
										cout << "Есть ещё операции, которые не отобразились!";
										work_interface.set_cursor_local(57, 31);
										cout << "Используйте расширенный поиск!";
									}
								} while (count_string >= 0 && counter_operations != 6);
							}
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
			}
			int choice;
			work_interface.set_cursor_local(78, 41);
			cin >> choice;
			return choice;
			break;
		}
		case 4:
		{
			// Страница выхода
			work_interface.interface_exit_page();
			int exit_or_restart;
			work_interface.set_cursor_local(48, 11);
			cin >> exit_or_restart;
			if (exit_or_restart == 1)
			{
				return 0;
			}
			else
			{
				return 1;
			}
			system("pause");
			break;
		}
	}
}

void Account::check_return_cash()
{
	Console notifications;
	string date_return_deposit, date_now;
	SYSTEMTIME stime_return_cash;
	GetLocalTime(&stime_return_cash);
	ofstream file_date_write("check.txt", ios_base::out);
	file_date_write << stime_return_cash.wDay << " " << stime_return_cash.wMonth << " " << stime_return_cash.wYear;
	file_date_write.close();
	ifstream file_date_read("check.txt");
	getline(file_date_read, date_now);
	remove("check.txt");
	ifstream file_deposit(login + deposit + expansion);
	int count_deposit;
	file_deposit >> count_deposit;
	int i = 0;
	string date_part[3];
	int count_return = 0;
	int cash_deposit;
	vector<int>counter_delete_deposits; // Номер вклада, который нужно удалить (их в один день может быть несколько)
	while (i != count_deposit)
	{
		file_deposit >> cash_deposit;
		file_deposit >> date_part[0];
		file_deposit >> date_part[1];
		file_deposit >> date_part[2];
		date_return_deposit = date_part[0] + " " + date_part[1] + " " + date_part[2];
		if (date_return_deposit == date_now)
		{
			Logic logic_return_cash;
			logic_return_cash.return_cash_of_deposit(cash_deposit, login);
			notifications.set_cursor_local(6, 33);
			cout << "СООБЩЕНИЕ ОТ БАНКА: Выполнено автоматическое пополнение счета после окончания срока вклада!";
			counter_delete_deposits.push_back(i);
			count_return++;
		}
		i++;
	}
	file_deposit.close();
	if (count_return == 0);
	else
	{
		count_deposit = count_deposit - count_return;
		ifstream file_deposit_read(login + deposit + expansion);
		vector <string> data;
		string line;
		i = 0;
		while (!file_deposit_read.eof())
		{
			getline(file_deposit_read, line);
			if (i > 0)
			{
				data.push_back(line);
			}
			i++;
		}
		file_deposit_read.close();
		if (count_deposit == 0)
		{
			ofstream file_deposit_rewrite(login + deposit + expansion, ios_base::out);
			file_deposit_rewrite << 0;
		}
		else
		{
			ofstream file_deposit_rewrite(login + deposit + expansion, ios_base::out);
			file_deposit_rewrite << count_deposit;
			int number_deposit = 0; // Номер вклада клиента
			int no_deleted = 0; // Счетчик для того, чтобы понять, сколько вкладов завершено
			for (i = 0; i < data.size(); i = i + 2)
			{
				for (int j = 0; j < counter_delete_deposits.size(); j++)
				{
					if (number_deposit == counter_delete_deposits[j])
					{
						break;
					}
					else
					{
						file_deposit_rewrite << endl << data[i] << endl << data[i + 1];
						no_deleted++;
					}
				}
				number_deposit++;
			}
			file_deposit_rewrite.close();
		}
	}
}

void Account::check_return_credit()
{
	int date[3];
	ifstream file_credit_read(login + credit + expansion);
	Console notifications;
	SYSTEMTIME stime_return_credit;
	GetLocalTime(&stime_return_credit);
	for (int i = 0; i < 3; i++)
	{
		file_credit_read >> date[i];
	}
	if (stime_return_credit.wYear > date[2])
	{
		notifications.set_cursor_local(27, 33);
		cout << "СООБЩЕНИЕ ОТ БАНКА: Пора погасить долг по кредиту!";
	}
	else
	{
		if (stime_return_credit.wMonth > date[1])
		{
			if (stime_return_credit.wDay >= date[0])
			{
				notifications.set_cursor_local(27, 33);
				cout << "СООБЩЕНИЕ ОТ БАНКА: Пора погасить долг по кредиту!";
			}
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
				interface_myData.set_cursor_local(28, 3 * choise);
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
			interface_myData.set_cursor_local(1, 41);
			system("pause");
		}
		break;
	}
	case 2:
	{
		interface_myData.interface_myTheme();
		int choice;
		ifstream file_Theme_read(login + Theme + expansion);
		file_Theme_read >> choice;
		file_Theme_read.close();
		interface_myData.interface_backgroud_topic_partially(choice);
		interface_myData.set_cursor_local(1, 9);
		cout << "Ваш выбор: ";
		cin >> choice;
		interface_myData.interface_backgroud_topic(choice);
		ofstream file_Theme_write(login + Theme + expansion, ios_base::out);
		file_Theme_write << choice;
		file_Theme_write.close();
		break;
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
	bool print;
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
					print = false;
					do
					{
						cin >> confirmation;
						if (confirmation == "Да")
						{
							logic_refill_card.operations(1, cash, true, login);
							system("cls");

							SYSTEMTIME stime;
							GetLocalTime(&stime);
							ifstream file_history_read(login + history_operation + expansion);
							if (file_history_read.is_open())
							{
								ofstream file_history_write(login + history_operation + expansion, ios_base::app);
								file_history_write << endl << logic_refill_card << endl << stime.wDayOfWeek << endl << stime.wDay << " " << stime.wMonth << " " << stime.wYear << endl << "ПОПОЛНЕНИЕ БАНКОВСКОЙ КАРТЫ" << endl << "новая операция";
								file_history_write.close();
							}
							else
							{
								ofstream file_history_write(login + history_operation + expansion, ios_base::app);
								file_history_write << logic_refill_card << endl << stime.wDayOfWeek << endl << stime.wDay << " " << stime.wMonth << " " << stime.wYear << endl << "ПОПОЛНЕНИЕ БАНКОВСКОЙ КАРТЫ" << endl << "новая операция";
							}
							file_history_read.close();

							interface_operation.set_cursor_local(34, 15);
							cout << "ЗАЧИСЛЕНО " << logic_refill_card << " RUB НА ВАШУ КАРТУ!" << endl;;
							system("pause");
							print = true;
							break;
						}
						else if (confirmation == "Нет")
						{
							print = true;
							break;
						}
						else
						{
							print = true;
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
					interface_operation.set_cursor_local(4, 21);
					system("pause");
					break;
				}
			}
		}
		file_film.close();
		break;
	}
	case 2:
	{
		interface_operation.interface_operation(2);
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
					string number_card, name_recipient;
					interface_operation.set_cursor_local(40, 4);
					cout << cash;
					interface_operation.set_cursor_local(40, 7);
					cin >> number_card;
					interface_operation.set_cursor_local(40, 10);
					cin >> name_recipient;
					interface_operation.set_cursor_local(40, 13);
					cin >> logic_refill_card;
					new_cash = logic_refill_card.operations(2, cash, false, login);
					if (new_cash == 500000000)
					{
						system("cls");
						interface_operation.set_cursor_local(37, 15);
						cout << "НЕДОСТАТОЧНО СРЕДТСТВ!!!";
						interface_operation.set_cursor_local(1, 40);
						system("pause");
						break;
					}
					else
					{
						interface_operation.set_cursor_local(40, 16);
						cout << new_cash;
					}
					interface_operation.set_cursor_local(1, 19);
					cout << "Подтверждаете операцию? ";
					do
					{
						cin >> confirmation;
						if (confirmation == "Да")
						{
							logic_refill_card.operations(2, new_cash, true, login);
							system("cls");

							SYSTEMTIME stime;
							GetLocalTime(&stime);
							ifstream file_history_read(login + history_operation + expansion);
							if (file_history_read.is_open())
							{
								ofstream file_history_write(login + history_operation + expansion, ios_base::app);
								file_history_write << endl << name_recipient  << endl << logic_refill_card << endl << stime.wDayOfWeek << endl << stime.wDay << " " << stime.wMonth << " " << stime.wYear << endl << "ПЕРЕВОД КЛИЕНТУ МаксиБанк" << endl << "новая операция";
								file_history_write.close();
							}
							else
							{
								ofstream file_history_write(login + history_operation + expansion, ios_base::app);
								file_history_write << name_recipient  << endl << logic_refill_card << endl << stime.wDayOfWeek << endl << stime.wDay << " " << stime.wMonth << " " << stime.wYear << endl << "ПЕРЕВОД КЛИЕНТУ МаксиБанк" << endl << "новая операция";
							}
							file_history_read.close();
							interface_operation.set_cursor_local(34, 15);
							cout << "ОТПРАВЛЕНО " << logic_refill_card << " RUB НА КАРТУ Макси-банка " << number_card << "!" << endl;
							interface_operation.set_cursor_local(1, 40);
							system("pause");
							print = true;
						}
						else if (confirmation == "Нет")
						{
							print = true;
							interface_operation.set_cursor_local(1, 40);
							system("pause");
							break;
						}
					} while (print != true);
					break;
				}
				else
				{
					system("cls");
					interface_operation.set_cursor_local(34, 15);
					cout << "НЕПРАВИЛЬНЫЙ ОТВЕТ НА ВОПРОС!";
					interface_operation.set_cursor_local(4, 16);
					cout << "В целях безопасности банк не может провести операцию, пока вы не дадите правильный ответ на вопрос!";
					interface_operation.set_cursor_local(4, 21);
					system("pause");
					break;
				}
			}
		}
		file_film.close();
		break;
	}
	case 3:
	{
		interface_operation.interface_operation(3);
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
					string number_card, name_recipient, name_bank;
					interface_operation.set_cursor_local(40, 4);
					cout << cash;
					interface_operation.set_cursor_local(40, 7);
					cin >> name_bank;
					interface_operation.set_cursor_local(40, 10);
					cin >> number_card;
					interface_operation.set_cursor_local(40, 13);
					cin >> name_recipient;
					interface_operation.set_cursor_local(40, 16);
					cin >> logic_refill_card;
					new_cash = logic_refill_card.operations(3, cash, false, login);
					if (new_cash == 500000000)
					{
						system("cls");
						interface_operation.set_cursor_local(37, 15);
						cout << "НЕДОСТАТОЧНО СРЕДТСТВ!!!";
						interface_operation.set_cursor_local(1, 40);
						system("pause");
						break;
					}
					else
					{
						interface_operation.set_cursor_local(40, 19);
						cout << new_cash;
					}
					interface_operation.set_cursor_local(1, 22);
					cout << "Подтверждаете операцию? ";
					do
					{
						cin >> confirmation;
						if (confirmation == "Да")
						{
							logic_refill_card.operations(3, new_cash, true, login);
							system("cls");

							SYSTEMTIME stime;
							GetLocalTime(&stime);
							ifstream file_history_read(login + history_operation + expansion);
							if (file_history_read.is_open())
							{
								ofstream file_history_write(login + history_operation + expansion, ios_base::app);
								file_history_write << endl << name_recipient << endl << logic_refill_card << endl << stime.wDayOfWeek << endl << stime.wDay << " " << stime.wMonth << " " << stime.wYear << endl << "ПЕРЕВОД КЛИЕНТУ ДРУГОГО БАНКА" << endl << "новая операция";
								file_history_write.close();
							}
							else
							{
								ofstream file_history_write(login + history_operation + expansion, ios_base::app);
								file_history_write << name_recipient << endl << logic_refill_card << endl << stime.wDayOfWeek << endl << stime.wDay << " " << stime.wMonth << " " << stime.wYear << endl << "ПЕРЕВОД КЛИЕНТУ ДРУГОГО БАНКА" << endl << "новая операция";
							}
							file_history_read.close();
							interface_operation.set_cursor_local(34, 15);
							cout << "ОТПРАВЛЕНО " << logic_refill_card << " RUB НА КАРТУ БАНКА '" << name_bank << "' " << number_card << "!" << endl;
							interface_operation.set_cursor_local(1, 40);
							system("pause");
							print = true;
						}
						else if (confirmation == "Нет")
						{
							print = true;
							interface_operation.set_cursor_local(1, 40);
							system("pause");
							break;
						}
					} while (print != true);
					break;
				}
				else
				{
					system("cls");
					interface_operation.set_cursor_local(34, 15);
					cout << "НЕПРАВИЛЬНЫЙ ОТВЕТ НА ВОПРОС!";
					interface_operation.set_cursor_local(4, 16);
					cout << "В целях безопасности банк не может провести операцию, пока вы не дадите правильный ответ на вопрос!";
					interface_operation.set_cursor_local(4, 21);
					system("pause");
					break;
				}
			}
		}
		file_film.close();
		break;
	}
	case 4:
	{
		interface_operation.interface_operation(4);
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
					string number_phone;
					interface_operation.set_cursor_local(40, 4);
					cout << cash;
					interface_operation.set_cursor_local(40, 7);
					cin >> number_phone;
					interface_operation.set_cursor_local(40, 10);
					cin >> logic_refill_card;
					new_cash = logic_refill_card.operations(4, cash, false, login);
					if (new_cash == 500000000)
					{
						system("cls");
						interface_operation.set_cursor_local(37, 15);
						cout << "НЕДОСТАТОЧНО СРЕДТСТВ!!!";
						interface_operation.set_cursor_local(1, 40);
						system("pause");
						break;
					}
					else
					{
						interface_operation.set_cursor_local(40, 13);
						cout << new_cash;
					}
					interface_operation.set_cursor_local(1, 16);
					cout << "Подтверждаете операцию? ";
					do
					{
						cin >> confirmation;
						if (confirmation == "Да")
						{
							logic_refill_card.operations(4, new_cash, true, login);
							system("cls");

							SYSTEMTIME stime;
							GetLocalTime(&stime);
							ifstream file_history_read(login + history_operation + expansion);
							if (file_history_read.is_open())
							{
								ofstream file_history_write(login + history_operation + expansion, ios_base::app);
								file_history_write << endl << number_phone << endl << logic_refill_card << endl << stime.wDayOfWeek << endl << stime.wDay << " " << stime.wMonth << " " << stime.wYear << endl << "ОПЛАТА СОТОВОЙ СВЯЗИ" << endl << "новая операция";
								file_history_write.close();
							}
							else
							{
								ofstream file_history_write(login + history_operation + expansion, ios_base::app);
								file_history_write << number_phone << endl << logic_refill_card << endl << stime.wDayOfWeek << endl << stime.wDay << " " << stime.wMonth << " " << stime.wYear << endl << "ОПЛАТА СОТОВОЙ СВЯЗИ" << endl << "новая операция";
							}
							file_history_read.close();
							interface_operation.set_cursor_local(34, 15);
							cout << "ОТПРАВЛЕНО " << logic_refill_card << " RUB НА НОМЕР ТЕЛЕФОНА " << number_phone << "!" << endl;
							interface_operation.set_cursor_local(1, 40);
							system("pause");
							print = true;
						}
						else if (confirmation == "Нет")
						{
							print = true;
							interface_operation.set_cursor_local(1, 40);
							system("pause");
							break;
						}
					} while (print != true);
					break;
				}
				else
				{
					system("cls");
					interface_operation.set_cursor_local(34, 15);
					cout << "НЕПРАВИЛЬНЫЙ ОТВЕТ НА ВОПРОС!";
					interface_operation.set_cursor_local(4, 16);
					cout << "В целях безопасности банк не может провести операцию, пока вы не дадите правильный ответ на вопрос!";
					interface_operation.set_cursor_local(4, 21);
					system("pause");
					break;
				}
			}
		}
		file_film.close();
		break;
	}
	case 5:
	{
		int count_deposits;
		bool check_count_deposits;
		ifstream file_deposit(login + deposit + expansion);
		if (file_deposit.is_open())
		{
			file_deposit >> count_deposits;
			if (count_deposits == 3)
			{
				interface_operation.set_cursor_local(9, 19);
				cout << "У Вас уже открыто три вклада! Наш банк не предоставляет ведение сразу 4 и более вкладов!";
				check_count_deposits = false;
			}
			else
			{
				check_count_deposits = true;
			}
		}
		else
		{
			check_count_deposits = true;
		}
		file_deposit.close();
		if (check_count_deposits == true)
		{
			interface_operation.interface_operation(5);
			unsigned long int all_return;
			interface_operation.set_cursor_local(80, 1);
			cin >> favourite_film;
			ifstream file_film(login + expansion);
			int year = 0, month = 0, day = 0;
			SYSTEMTIME stime_return_deposit;
			GetLocalTime(&stime_return_deposit);
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
						interface_operation.interface_local_operation(5);
						file_film >> cash;
						interface_operation.set_cursor_local(47, 3);
						cout << cash << "   RUB";						
						if (number_of_deposit == "1")
						{
							Logic logic_deposit(30, 1095);
							interface_operation.set_cursor_local(47, 6);
							cin >> logic_deposit;
							logic_refill_card = logic_deposit;
							new_cash = logic_deposit.operations(5, cash, false, login);
							if (new_cash == 500000000)
							{
								system("cls");
								interface_operation.set_cursor_local(37, 15);
								cout << "НЕДОСТАТОЧНО СРЕДТСТВ!!!";
								interface_operation.set_cursor_local(1, 40);
								system("pause");
								break;
							}
							else
							{
								interface_operation.set_cursor_local(47, 9);
								cout << new_cash;
							}
							unsigned long int percent_cash = logic_deposit.amount_of_income();
							interface_operation.set_cursor_local(47, 12);
							cout << percent_cash;
							all_return = logic_deposit.amount_all_return();
							interface_operation.set_cursor_local(47, 15);
							cout << all_return;
							int days = 1095;
							if (days >= 365)
							{
								year = 0;
								while (days >= 365)
								{
									year++;
									days = days - 365;
								}
							}
							if (days >= 30)
							{
								month = 0;
								while (days >= 30)
								{
									month++;
									days = days - 30;
								}
							}
							day = 0;
							while (days != 0)
							{
								day++;
								days = days - 1;
							}
						}
						if (number_of_deposit == "2")
						{
							Logic logic_deposit(10, 182);
							interface_operation.set_cursor_local(47, 6);
							cin >> logic_deposit;
							logic_refill_card = logic_deposit;
							new_cash = logic_deposit.operations(5, cash, false, login);
							if (new_cash == 500000000)
							{
								system("cls");
								interface_operation.set_cursor_local(37, 15);
								cout << "НЕДОСТАТОЧНО СРЕДТСТВ!!!";
								interface_operation.set_cursor_local(1, 40);
								system("pause");
								break;
							}
							else
							{
								interface_operation.set_cursor_local(47, 9);
								cout << new_cash;
							}
							unsigned long int percent_cash = logic_deposit.amount_of_income();
							interface_operation.set_cursor_local(47, 12);
							cout << percent_cash;
							all_return = logic_deposit.amount_all_return();
							interface_operation.set_cursor_local(47, 15);
							cout << all_return;
							int days = 182;
							if (days >= 30)
							{
								month = 0;
								while (days >= 30)
								{
									month++;
									days = days - 30;
								}
							}
							day = 0;
							while (days != 0)
							{
								day++;
								days = days - 1;
							}
						}
						if (number_of_deposit == "3")
						{
							Logic logic_deposit(5, 365);
							interface_operation.set_cursor_local(47, 6);
							cin >> logic_deposit;
							logic_refill_card = logic_deposit;
							new_cash = logic_deposit.operations(5, cash, false, login);
							if (new_cash == 500000000)
							{
								system("cls");
								interface_operation.set_cursor_local(37, 15);
								cout << "НЕДОСТАТОЧНО СРЕДТСТВ!!!";
								interface_operation.set_cursor_local(1, 40);
								system("pause");
								break;
							}
							else
							{
								interface_operation.set_cursor_local(47, 9);
								cout << new_cash;
							}
							unsigned long int percent_cash = logic_deposit.amount_of_income();
							interface_operation.set_cursor_local(47, 12);
							cout << percent_cash;
							all_return = logic_deposit.amount_all_return();
							interface_operation.set_cursor_local(47, 15);
							cout << all_return;
							int days = 365;
							if (days >= 365)
							{
								year = 0;
								while (days >= 365)
								{
									year++;
									days = days - 365;
								}
							}
							if (days >= 30)
							{
								month = 0;
								while (days >= 30)
								{
									month++;
									days = days - 30;
								}
							}
							day = 0;
							while (days != 0)
							{
								day++;
								days = days - 1;
							}
						}
						file_film.close();
						interface_operation.set_cursor_local(1, 19);
						cout << "Подтверждаете операцию? ";
						do
						{
							cin >> confirmation;
							if (confirmation == "Да")
							{
								logic_refill_card.operations(5, new_cash, true, login);
								system("cls");

								SYSTEMTIME stime_deposit;
								GetLocalTime(&stime_deposit);
								ifstream file_history_read(login + history_operation + expansion);
								if (file_history_read.is_open())
								{
									ofstream file_history_write(login + history_operation + expansion, ios_base::app);
									file_history_write << endl << all_return << endl << logic_refill_card << endl << stime_deposit.wDayOfWeek << endl << stime_deposit.wDay << " " << stime_deposit.wMonth << " " << stime_deposit.wYear << endl << "ОТКРЫТИЕ ВКЛАДА" << endl << "новая операция";
									file_history_write.close();
								}
								else
								{
									ofstream file_history_write(login + history_operation + expansion, ios_base::app);
									file_history_write << all_return << endl << logic_refill_card << endl << stime_deposit.wDayOfWeek << endl << stime_deposit.wDay << " " << stime_deposit.wMonth << " " << stime_deposit.wYear << endl << "ОТКРЫТИЕ ВКЛАДА" << endl << "новая операция";
									file_history_write.close();
								}
								file_history_read.close();
								ifstream file_deposit_read(login + deposit + expansion);
								if (file_deposit_read.is_open())
								{
									string line;
									file_deposit_read >> line;
									if (line == "0")
									{
										file_deposit_read.close();
										ofstream file_deposit_write(login + deposit + expansion, ios_base::out);
										file_deposit_write << "1" << endl << all_return << endl << stime_return_deposit.wDay + day << " " << stime_return_deposit.wMonth + month << " " << stime_return_deposit.wYear + year;
										file_deposit_write.close();
									}
									else
									{
										vector <string> data;
										int i = 0;
										while (!file_deposit_read.eof())
										{
											getline(file_deposit_read, line);
											if (i > 0)
											{
												data.push_back(line);
											}
											i++;
										}
										file_deposit_read.close();
										count_deposits++;
										ofstream file_deposit_write(login + deposit + expansion, ios_base::out);
										file_deposit_write << count_deposits << endl;
										for (int i = 0; i < data.size(); i++)
										{
											file_deposit_write << data[i] << endl;
										}
										file_deposit_write << all_return << endl << stime_return_deposit.wDay + day << " " << stime_return_deposit.wMonth + month << " " << stime_return_deposit.wYear + year;
										file_deposit_write.close();
									}
								}
								else
								{
									ofstream file_deposit_write(login + deposit + expansion, ios_base::out);
									file_deposit_write << "1" << endl << all_return << endl << stime_return_deposit.wDay + day << " " << stime_return_deposit.wMonth + month << " " << stime_return_deposit.wYear + year;
									file_deposit_write.close();
								}
								interface_operation.set_cursor_local(34, 15);
								cout << "ВКЛАД ОТКРЫТ!";
								interface_operation.set_cursor_local(9, 16);
								cout << "Если вы зайдете в личный кабинет " << stime_return_deposit.wDay + day << " " << stime_return_deposit.wMonth + month << " " << stime_return_deposit.wYear + year << " , то Ваш счет мы автоматически пополним!";
								interface_operation.set_cursor_local(4, 17);
								system("pause");
								print = true;
							}
							else if (confirmation == "Нет")
							{
								print = true;
								break;
							}
						} while (print != true);
					}
					else
					{
						system("cls");
						interface_operation.set_cursor_local(34, 15);
						cout << "НЕПРАВИЛЬНЫЙ ОТВЕТ НА ВОПРОС!";
						interface_operation.set_cursor_local(4, 16);
						cout << "В целях безопасности банк не может провести операцию, пока вы не дадите правильный ответ на вопрос!";
						interface_operation.set_cursor_local(4, 21);
						system("pause");
						break;
					}
				}
			}
		}
		break;
	}
	case 6:
	{
		ifstream file_trust(login + credit + expansion);
		if (file_trust.is_open())
		{
			file_trust.close();
			interface_operation.set_cursor_local(37, 19);
			cout << "Вы уже взяли один кредит в нашем банке!";
			interface_operation.set_cursor_local(30, 20);
			cout << "Для выполнения операции погасите нынешний кредит!";
		}
		else
		{
			interface_operation.interface_operation(6);
			interface_operation.set_cursor_local(80, 1);
			int months; // Сюда записывается срок кредита, который ввёл пользователь
			cin >> favourite_film;
			string choice_credit;
			unsigned long int month_payment, all_payment;
			ifstream file_film(login + expansion);
			for (int i = 0; i < 11; i++)
			{
				file_film >> checking;
				if (i == 10)
				{
					if (checking == favourite_film)
					{
						interface_operation.set_cursor_local(67, 3);
						cout << "Выберите вид кредита: ";
						cin >> choice_credit;
						if (choice_credit == "Потребительский")
						{
							Logic logic_trust(15);
							interface_operation.interface_local_operation(6);
							file_film >> cash;
							interface_operation.set_cursor_local(38, 3);
							cout << cash << "   RUB";
							interface_operation.set_cursor_local(38, 6);
							cin >> months;
							bool check;
							do
							{
								interface_operation.set_cursor_local(38, 9);
								cin >> logic_trust;
								check = logic_trust.checking(1);
								if (check == false)
								{
									interface_operation.set_cursor_local(1, 25);
									cout << "Наш банк не выдаёт потребительский кредит на сумму больше 5млн!";
									interface_operation.set_cursor_local(38, 9);
									cout << "        ";
								}
							} while (check != true);
							logic_refill_card = logic_trust;
							month_payment = logic_trust.monthly_payment(months);
							interface_operation.set_cursor_local(38, 12);
							cout << month_payment;
							all_payment = logic_trust.all_payment();
							interface_operation.set_cursor_local(38, 15);
							cout << all_payment;
							interface_operation.set_cursor_local(38, 18);
							new_cash = logic_trust.operations(6, cash, false, login);
							cout << new_cash;
						}
						else if (choice_credit == "Ипотека")
						{
							Logic logic_trust(10);
							interface_operation.interface_local_operation(6);
							file_film >> cash;
							interface_operation.set_cursor_local(38, 3);
							cout << cash << "   RUB";
							interface_operation.set_cursor_local(38, 6);
							cin >> months;
							bool check;
							do
							{
								interface_operation.set_cursor_local(38, 9);
								cin >> logic_trust;
								check = logic_trust.checking(2);
								if (check == false)
								{
									interface_operation.set_cursor_local(1, 25);
									cout << "Наш банк не выдаёт ипотеку на сумму больше 30млн!";
									interface_operation.set_cursor_local(38, 9);
									cout << "        ";
								}
							} while (check != true);
							logic_refill_card = logic_trust;
							month_payment = logic_trust.monthly_payment(months);
							interface_operation.set_cursor_local(38, 12);
							cout << month_payment;
							all_payment = logic_trust.all_payment();
							interface_operation.set_cursor_local(38, 15);
							cout << all_payment;
							interface_operation.set_cursor_local(38, 18);
							new_cash = logic_trust.operations(6, cash, false, login);
							cout << new_cash;
						}
						else if (choice_credit == "Автокредит")
						{
							Logic logic_trust(14);
							interface_operation.interface_local_operation(6);
							file_film >> cash;
							interface_operation.set_cursor_local(38, 3);
							cout << cash << "   RUB";
							interface_operation.set_cursor_local(38, 6);
							cin >> months;
							bool check;
							do
							{
								interface_operation.set_cursor_local(38, 9);
								cin >> logic_trust;
								check = logic_trust.checking(3);
								if (check == false)
								{
									interface_operation.set_cursor_local(1, 25);
									cout << "Наш банк не выдаёт автокредит на сумму больше 5млн!";
									interface_operation.set_cursor_local(38, 9);
									cout << "        ";
								}
							} while (check != true);
							logic_refill_card = logic_trust;
							month_payment = logic_trust.monthly_payment(months);
							interface_operation.set_cursor_local(38, 12);
							cout << month_payment;
							all_payment = logic_trust.all_payment();
							interface_operation.set_cursor_local(38, 15);
							cout << all_payment;
							interface_operation.set_cursor_local(38, 18);
							new_cash = logic_trust.operations(6, cash, false, login);
							cout << new_cash;
						}
						file_film.close();
						interface_operation.set_cursor_local(1, 25);
						cout << "                                                    ";
						interface_operation.set_cursor_local(1, 25);
						cout << "Подтверждаете операцию? ";
						do
						{
							cin >> confirmation;
							if (confirmation == "Да")
							{
								logic_refill_card.operations(6, cash, true, login);
								system("cls");

								SYSTEMTIME stime_credit;
								GetLocalTime(&stime_credit);
								ifstream file_history_read(login + history_operation + expansion);
								if (file_history_read.is_open())
								{
									ofstream file_history_write(login + history_operation + expansion, ios_base::app);
									file_history_write << endl << logic_refill_card << endl << stime_credit.wDayOfWeek << endl << stime_credit.wDay << " " << stime_credit.wMonth << " " << stime_credit.wYear << endl << "ПОЛУЧЕНИЕ КРЕДИТА" << endl << "новая операция";
									file_history_write.close();
								}
								else
								{
									ofstream file_history_write(login + history_operation + expansion, ios_base::app);
									file_history_write << logic_refill_card << endl << stime_credit.wDayOfWeek << endl << stime_credit.wDay << " " << stime_credit.wMonth << " " << stime_credit.wYear << endl << "ПОЛУЧЕНИЕ КРЕДИТА" << endl << "новая операция";
									file_history_write.close();
								}
								file_history_read.close();
								ofstream file_trust(login + credit + expansion, ios_base::app);
								file_trust << stime_credit.wDay << " " << stime_credit.wMonth << " " << stime_credit.wYear << endl << month_payment << endl << all_payment;
								file_trust.close();
								interface_operation.set_cursor_local(34, 15);
								cout << "Получение кредита на сумму " << logic_refill_card << " RUB выполнено!";
								print = true;
							}
							else if (confirmation == "Нет")
							{
								print = true;
								break;
							}
						} while (print != true);
						interface_operation.set_cursor_local(4, 21);
						system("pause");
						break;
					}
					else
					{
						system("cls");
						interface_operation.set_cursor_local(34, 15);
						cout << "НЕПРАВИЛЬНЫЙ ОТВЕТ НА ВОПРОС!";
						interface_operation.set_cursor_local(4, 16);
						cout << "В целях безопасности банк не может провести операцию, пока вы не дадите правильный ответ на вопрос!";
						interface_operation.set_cursor_local(4, 21);
						system("pause");
						break;
					}
				}
			}
			
		}
		break;
	}
	case 7:
	{
		ifstream credit_file(login + credit + expansion);
		if (!credit_file.is_open())
		{
			interface_operation.set_cursor_local(34, 15);
			cout << "У Вас нет долгов перед банком!";
			interface_operation.set_cursor_local(1, 40);
			system("pause");
		}
		else
		{
			string line;
			getline(credit_file, line);
			if (line == "0")
			{
				interface_operation.set_cursor_local(34, 15);
				cout << "У Вас нет долгов перед банком!";
				credit_file.close();
				interface_operation.set_cursor_local(1, 40);
				system("pause");
			}
			else
			{
				interface_operation.interface_operation(7);
				unsigned long int monthly_cash;
				unsigned long int all_sum_credit;
				credit_file >> monthly_cash >> all_sum_credit;
				interface_operation.set_cursor_local(56, 3);
				cout << monthly_cash;
				interface_operation.set_cursor_local(56, 6);
				cout << all_sum_credit;
				interface_operation.set_cursor_local(56, 9);
				cout << monthly_cash;
				logic_refill_card.set_new_cash(monthly_cash);
				string name_file = login + credit + expansion;
				all_sum_credit = logic_refill_card.loan_repayment(all_sum_credit);
				interface_operation.set_cursor_local(56, 12);
				cout << all_sum_credit;
				ifstream file_data(login + expansion);
				while (!file_data.eof())
				{
					getline(file_data, line);
				}
				file_data.close();
				unsigned long int client_cash = stoi(line);
				client_cash = logic_refill_card.operations(7, client_cash, false, login);
				if (client_cash == 500000000)
				{
					system("cls");
					interface_operation.set_cursor_local(37, 15);
					cout << "НЕДОСТАТОЧНО СРЕДТСТВ!!!";
					interface_operation.set_cursor_local(1, 40);
					system("pause");
					break;
				}
				else
				{
					interface_operation.set_cursor_local(56, 15);
					cout << client_cash;
				}
				interface_operation.set_cursor_local(1, 18);
				cout << "Подтверждаете операцию? ";
				do
				{
					cin >> confirmation;
					if (confirmation == "Да")
					{
						logic_refill_card.operations(7, client_cash, true, login);
						system("cls");
						SYSTEMTIME stime_credit;
						GetLocalTime(&stime_credit);
						ifstream file_history_read(login + history_operation + expansion);
						if (file_history_read.is_open())
						{
							ofstream file_history_write(login + history_operation + expansion, ios_base::app);
							file_history_write << endl << logic_refill_card << endl << stime_credit.wDayOfWeek << endl << stime_credit.wDay << " " << stime_credit.wMonth << " " << stime_credit.wYear << endl << "ПОГАШЕНИЕ КРЕДИТА" << endl << "новая операция";
							file_history_write.close();
						}
						else
						{
							ofstream file_history_write(login + history_operation + expansion, ios_base::out);
							file_history_write << logic_refill_card << endl << stime_credit.wDayOfWeek << endl << stime_credit.wDay << " " << stime_credit.wMonth << " " << stime_credit.wYear << endl << "ПОГАШЕНИЕ КРЕДИТА" << endl << "новая операция";
							file_history_write.close();
						}
						file_history_read.close();
						ofstream file_trust(login + credit + expansion, ios_base::out);
						if (all_sum_credit != 0)
						{
							file_trust << stime_credit.wDay << " " << stime_credit.wMonth << " " << stime_credit.wYear << endl << monthly_cash << endl << all_sum_credit;
							interface_operation.set_cursor_local(34, 15);
							cout << "Погашение кредита на сумму " << logic_refill_card << " RUB выполнено!";

						}
						else
						{
							file_trust << 0;
							interface_operation.set_cursor_local(34, 15);
							cout << "Вы полностью закрыли долг по кредиту!";
						}
						file_trust.close();
						print = true;
					}
					else if (confirmation == "Нет")
					{
						print = true;
						break;
					}
				} while (print != true);
				credit_file.close();
				interface_operation.set_cursor_local(1, 40);
				system("pause");
			}
		}
		break;
	}
	}
}

void Account::advanced_search(vector<string>advanced_search_operation)
{
	Console inerface_advanced_search;
	Logic logic_advanced_search;
	inerface_advanced_search.set_cursor_local(57, 15);
	int X = 10;
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
			if (day_operation == "7")
			{
				day_operation = "0";
			}
			check_kind = true;
			advanced_search_operation = logic_advanced_search.advanced_search(advanced_search_operation, name_operation, sum_cash, day_operation);
		}
		else if (kind == "2")
		{
			inerface_advanced_search.set_cursor_local(57, 20);
			cout << "Номер операции:";
			inerface_advanced_search.set_cursor_local(57, 21);
			cout << "Денежная сумма:";
			inerface_advanced_search.set_cursor_local(57, 22);
			cout << "Имя получателя:";
			inerface_advanced_search.set_cursor_local(57, 23);
			cout << "Номер дня недели:";
			int number_operation;
			inerface_advanced_search.set_cursor_local(73, 20);
			cin >> number_operation;
			name_operation = logic_advanced_search.number_operation_to_name_operation(number_operation);
			inerface_advanced_search.set_cursor_local(73, 21);
			cin >> sum_cash;
			string name;
			inerface_advanced_search.set_cursor_local(73, 22);
			cin >> name;
			inerface_advanced_search.set_cursor_local(75, 23);
			cin >> day_operation;
			if (day_operation == "7")
			{
				day_operation = "0";
			}
			check_kind = true;
			advanced_search_operation = logic_advanced_search.advanced_search(advanced_search_operation, name_operation, sum_cash, day_operation, name);
		}
		else if (kind == "3")
		{
			inerface_advanced_search.set_cursor_local(57, 20);
			cout << "Номер телефона:";
			inerface_advanced_search.set_cursor_local(57, 21);
			cout << "Денежная сумма:";
			inerface_advanced_search.set_cursor_local(57, 22);
			cout << "Номер дня недели:";
			string number_phone;
			inerface_advanced_search.set_cursor_local(73, 20);
			cin >> number_phone;
			name_operation = logic_advanced_search.number_operation_to_name_operation(4);
			inerface_advanced_search.set_cursor_local(73, 21);
			cin >> sum_cash;
			inerface_advanced_search.set_cursor_local(75, 22);
			cin >> day_operation;
			if (day_operation == "7")
			{
				day_operation = "0";
			}
			check_kind = true;
			advanced_search_operation = logic_advanced_search.advanced_search(advanced_search_operation, name_operation, sum_cash, day_operation, number_phone);
		}
		else
		{

		}
	} while (check_kind == false);
	int k = 0;
	int j = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int n = 0; n < 4; n++)
		{
			inerface_advanced_search.set_cursor_local(2, 7 + j + k);
			cout << "                                                  "; // Очищаю всю таблицу для обновления
			j++;
		}
		k = k + 2;
	}
	if (advanced_search_operation.size() == 0)
	{
		inerface_advanced_search.set_cursor_local(3, 9);
		cout << "По Вашему запросу ничего не найдено!";
	}
	else
	{
		int count_string = advanced_search_operation.size() - 1;
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
				if (i == 0 && (advanced_search_operation[count_string] == "ПЕРЕВОД КЛИЕНТУ МаксиБанк" || advanced_search_operation[count_string] == "ПЕРЕВОД КЛИЕНТУ ДРУГОГО БАНКА" || advanced_search_operation[count_string] == "ОПЛАТА СОТОВОЙ СВЯЗИ"))
				{
					X = 15;
					inerface_advanced_search.set_cursor_local(X, 7 + j + k);
					cout << advanced_search_operation[count_string];
					inerface_advanced_search.set_cursor_local(2, 8 + j + k);
					cout << advanced_search_operation[count_string - 4];
				}
				else if (i == 2)
				{
					inerface_advanced_search.set_cursor_local(X, 7 + j + k);
					cout << logic_advanced_search.number_day_to_name_day(advanced_search_operation[count_string]);
				}
				else if (i == 3)
				{
					inerface_advanced_search.set_cursor_local(X, 7 + j + k);
					cout << advanced_search_operation[count_string];
					inerface_advanced_search.set_cursor_local(X + 9, 7 + j + k);
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
					inerface_advanced_search.set_cursor_local(X, 7 + j + k);
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
			X = 10;
			k = k + 2;
		} while (count_string >= 0);
	}
}

int Account::get_number_Theme()
{
	ifstream file_Theme(login + Theme + expansion);
	int theme;
	file_Theme >> theme;
	file_Theme.close();
	return theme;
}