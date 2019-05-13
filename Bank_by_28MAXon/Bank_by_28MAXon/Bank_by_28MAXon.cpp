#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Console.h"
#include "Account.h"
#include "registration.h"
using namespace std;

int main()
{
	// Заголовок и кодировка
	system("title Онлайн-МаксиБанк");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Console work_with_console; // При помощи этого объекта класса будем работать с консолью

	// Программа автоматически выбирает фон, который пользователь выбирал в прошлый заход
	ifstream file_read("Accounts.txt");
	int choise_topic;
	file_read >> choise_topic;
	work_with_console.interface_backgroud_topic(choise_topic);

	/** Выбор фоновой темы
	cin >> choise_topic;
	work_with_console.interface_backgroud_topic(choise_topic);*/

	// Сохранение выбранного фона
	ofstream file_write("Accounts.txt", ios_base::out);
	file_write << choise_topic;
	file_write.close();

	work_with_console.interface_start_page(); // Работает с консолью для стартового окна банка
	Account men;
	Registration registration;
	int change;
	cout << "Ваш выбор: ";
	cin >> change;
	bool start;
	switch (change)
	{
		case 1:
		{
			do
			{
				work_with_console.interface_input();
				cin >> men;
				start = men.input();
				if (start == false)
				{
					work_with_console.set_cursor_local(1, 9);
					cout << "Неверный логин или пароль!!! Повторите ввод!" << endl << " ";
					system("pause");
				}
			} while (start != true);
			int choice_page = 1;
			while (choice_page != 4)
			{
				work_with_console.interface_menu(choice_page);
				work_with_console.interface_backgroud_topic_partially(choise_topic);
				choice_page = men.account_in_bank(choice_page);
			}
			break;
		}
		case 2:
		{
			bool confirm;
			do
			{
				work_with_console.interface_registration();
				cin >> registration;
				work_with_console.interface_backgroud_topic(choise_topic);
				work_with_console.interface_confirm();
				confirm = registration.confirmation();
			} while (confirm != true);
			system("pause");
			break;
		}
	}
	system("cls");
	cout << "Выход из приложения!" << endl;
	system("pause");
}