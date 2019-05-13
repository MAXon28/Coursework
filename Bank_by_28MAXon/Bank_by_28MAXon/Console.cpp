#include "pch.h"
#include "Console.h"
#include "Account.h"

void Console::interface_backgroud_topic(int choise)
{
	if (choise == 1)
	{
		system("color 2F");
	}
	if (choise == 2)
	{
		system("color B0");
	}
}

void Console::interface_start_page()
{
	system("cls");
	SetConsoleCursorPosition(hConsole, coordinates);
	cout << " Приветствуем Вас в нашем онлайн-банке! Для выполнения одного из вариантов ниже напишите ЦИФРУ, которая соответствует Вашему выбору!" << endl;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 3; i++)
	{
		set_cursor_local(1, i + 3);
		cout << "|";
		set_cursor_local(33, i + 3);
		cout << ".";
		set_cursor_local(68, i + 3);
		cout << "|";
	}
	set_cursor_local(2, 2);
	cout << "__________________________________________________________________" << endl;
	set_cursor_local(2, 5);
	cout << "__________________________________________________________________" << endl;
	set_cursor_local(3, 4);
	cout << " 1 - Вход в личный кабинет";
	set_cursor_local(35, 4);
	cout << " 2 - Регистрация в онлайн-банке";
	set_cursor_local(1, 7);
}

void Console::interface_input()
{
	system("cls");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	set_cursor_local(40, 0);
	cout << "ВХОД В ЛИЧНЫЙ КАБИНЕТ" << endl; 
	int y = 0;
	for (int i = 0; i < 2; i++)
	{
		set_cursor_local(2, 1 + y);
		cout << "_______________";
		set_cursor_local(2, 4 + y);
		cout << "_______________";
		set_cursor_local(18, 1 + y);
		cout << "_________________________";
		set_cursor_local(18, 4 + y);
		cout << "_________________________";
		y = y + 3;
	}

	for (int i = 0; i < 6; i++)
	{
		set_cursor_local(1, 2 + i);
		cout << "|";
		set_cursor_local(17, 2 + i);
		cout << "|";
		set_cursor_local(43, 2 + i);
		cout << "|";
	}
	set_cursor_local(7, 3);
	cout << "Логин";
	set_cursor_local(7, 6);
	cout << "Пароль";
}

void Console::interface_registration()
{
	system("cls");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	set_cursor_local(34, 0);
	SetConsoleCursorPosition(hConsole, coordinates);
	cout << "РЕГИСТРАЦИЯ В ОНЛАЙН-БАНКЕ" << endl;
	int y = 0;
	for (int i = 0; i < 11; i++)
	{
		set_cursor_local(2, 1 + y);
		cout << "___________________";
		set_cursor_local(2, 4 + y);
		cout << "___________________";
		set_cursor_local(22, 1 + y);
		cout << "___________________________________________";
		set_cursor_local(22, 4 + y);
		cout << "___________________________________________";
		y = y + 3;
	}

	for (int i = 0; i < 33; i++)
	{
		set_cursor_local(1, 2 + i);
		cout << "|";
		set_cursor_local(21, 2 + i);
		cout << "|";
		set_cursor_local(65, 2 + i);
		cout << "|";
	}
	set_cursor_local(3, 3);
	cout << "Имя";
	set_cursor_local(3, 6);
	cout << "Фамилия";
	set_cursor_local(3, 9);
	cout << "Возраст";
	set_cursor_local(3, 12);
	cout << "Номер телефона";
	set_cursor_local(3, 15);
	cout << "Электронная почта";
	set_cursor_local(3, 18);
	cout << "Гражданство";
	set_cursor_local(3, 21);
	cout << "Город проживания";
	set_cursor_local(3, 24);
	cout << "Номер карты";
	set_cursor_local(3, 27);
	cout << "Придумайте логин";
	set_cursor_local(3, 30);
	cout << "Придумайте пароль";
	set_cursor_local(3, 33);
	cout << "Имя Вашей мамы";
	color(15, 0);
}

void Console::interface_confirm()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	set_cursor_local(3, 3);
	cout << "Имя";
	set_cursor_local(3, 6);
	cout << "Фамилия";
	set_cursor_local(3, 9);
	cout << "Возраст";
	set_cursor_local(3, 12);
	cout << "Номер телефона";
	set_cursor_local(3, 15);
	cout << "Электронная почта";
	set_cursor_local(3, 18);
	cout << "Гражданство";
	set_cursor_local(3, 21);
	cout << "Город проживания";
	set_cursor_local(3, 24);
	cout << "Номер карты";
	set_cursor_local(3, 27);
	cout << "                 ";
	set_cursor_local(3, 27);
	cout << "Логин";
	set_cursor_local(3, 30);
	cout << "                 ";
	set_cursor_local(3, 30);
	cout << "Пароль";
	set_cursor_local(3, 33);
	cout << "Ваш любимый фильм";

	set_cursor_local(1, 36);
	cout << "Подтвердите регистрацию (нажмите цифру, соответствующую Вашему варианту ниже):";
	set_cursor_local(2, 37);
	cout << "____________________";
	set_cursor_local(2, 40);
	cout << "____________________";
	set_cursor_local(23, 37);
	cout << "____________________";
	set_cursor_local(23, 40);
	cout << "____________________";

	for (int i = 0; i < 3; i++)
	{
		set_cursor_local(1, 38 + i);
		cout << "|";
		set_cursor_local(22, 38 + i);
		cout << "|";
		set_cursor_local(43, 38 + i);
		cout << "|";
	}
	set_cursor_local(5, 39);
	cout << "1 - Подтверждаю";
	set_cursor_local(28, 39);
	cout << "2 - Назад";
	set_cursor_local(1, 42);
	cout << "Ваш выбор:";
}

void Console::interface_menu(int choice_page)
{
	system("cls");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 3; i++)
	{
		set_cursor_local(0, 0 + i);
		cout << "|";
		set_cursor_local(26, 0 + i);
		cout << "|";
		set_cursor_local(52, 0 + i);
		cout << "|";
		set_cursor_local(78, 0 + i);
		cout << "|";
		set_cursor_local(104, 0 + i);
		cout << "|";
	}
	int y = 0;
	for (int i = 0; i < 4; i++)
	{
		set_cursor_local(1 + y, 2);
		cout << "_________________________";
		y = y + 26;
	}
	set_cursor_local(4, 1);
	cout << "1 - главное меню";
	set_cursor_local(30, 1);
	cout << "2 - операции банка";
	set_cursor_local(56, 1);
	cout << "3 - история платежей";
	set_cursor_local(87, 1);
	cout << "4 - выход" << endl;
	
	switch (choice_page)
	{
	case 1:
	{
		color(14, 0);
		set_cursor_local(4, 1);
		cout << "1 - главное меню";
		break;
	}
	case 2:
	{
		color(14, 0);
		set_cursor_local(30, 1);
		cout << "2 - операции банка";
		break;
	}
	case 3:
	{
		color(14, 0);
		set_cursor_local(56, 1);
		cout << "3 - история платежей";
		break;
	}
	case 4:
	{
		color(14, 0);
		set_cursor_local(87, 1);
		cout << "4 - выход" << endl;
		break;
	}
	}
}

void Console::interface_main_page()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	set_cursor_local(34, 5);
	cout << "Главная страница онлайн-банка";
	set_cursor_local(0, 7);
	cout << "_________________________________________________________________________________________________________";
	set_cursor_local(37, 10);
	cout << "Денег на карте:";
	set_cursor_local(0, 13);
	cout << "_________________________________________________________________________________________________________";

	int y = 0;
	for (int i = 0; i < 3; i++)
	{
		set_cursor_local(38, 16 + y);
		cout << "___________________";
		y = y + 3;
	}
	for (int i = 0; i < 6; i++)
	{
		set_cursor_local(37, 17 + i);
		cout << "|";
		set_cursor_local(57, 17 + i);
		cout << "|";
	}
	set_cursor_local(43, 15);
	cout << "НАСТРОЙКИ";
	set_cursor_local(41, 18);
	cout << "1 - мои данные";
	set_cursor_local(40, 21);
	cout << "2 - изменить фон";
	set_cursor_local(40, 25);
	cout << "|Выберите действие|";
	set_cursor_local(1, 25);
	cout << "1 - настройки";
	set_cursor_local(90, 25);
	cout << "2 - меню";
	set_cursor_local(40, 26);
	cout << "|Ваш выбор:       |";
	set_cursor_local(1, 26);
	cout << "Номер в настройках:";
	set_cursor_local(81, 26);
	cout << "Номер кнопки в меню:";
}

void Console::interface_operations_page()
{
	set_cursor_local(43, 4);
	cout << "БАНКОВСКИЕ ОПЕРАЦИИ";
	int y = 0;
	for (int i = 0; i < 8; i++)
	{
		set_cursor_local(28, 5 + y);
		cout << "_____________________________________________";
		y = y + 3;
	}
	for (int i = 0; i < 21; i++)
	{
		set_cursor_local(27, 6 + i);
		cout << "|";
		set_cursor_local(73, 6 + i);
		cout << "|";
	}
	set_cursor_local(34, 7);
	cout << "1 - пополнить банковскую карту";
	set_cursor_local(34, 10);
	cout << "2 - перевод клиенту МаксиБанк";
	set_cursor_local(34, 13);
	cout << "3 - перевод клиенту другого банка";
	set_cursor_local(34, 16);
	cout << "4 - оплата сотовой связи";
	set_cursor_local(34, 19);
	cout << "5 - открыть вклад";
	set_cursor_local(34, 22);
	cout << "6 - взять кредит";
	set_cursor_local(34, 25);
	cout << "7 - погасить кредит";
	set_cursor_local(40, 28);
	cout << "|Выберите действие|";
	set_cursor_local(1, 28);
	cout << "1 - операции банка";
	set_cursor_local(90, 28);
	cout << "2 - меню";
	set_cursor_local(40, 29);
	cout << "|Ваш выбор:       |";
	set_cursor_local(1, 29);
	cout << "Номер операции:";
	set_cursor_local(81, 29);
	cout << "Номер кнопки в меню:";
}

void Console::interface_history_page()
{
	set_cursor_local(34, 4);
	cout << "ИСТОРИИ БАНКОВСКИХ ОПЕРАЦИЙ";
	for (int i = 0; i < 36; i++)
	{
		set_cursor_local(0, 6 + i);
		cout << "|";
		set_cursor_local(55, 6 + i);
		cout << "|";
	}
	int y = 0;
	for (int i = 0; i < 7; i++)
	{
		set_cursor_local(1, 5 + y);
		cout << "______________________________________________________";
		y = y + 6;
	}
	set_cursor_local(57, 6);
	cout << "1 - поиск банковских операций в истории";
	set_cursor_local(57, 7);
	cout << "2 - работа с меню";
	set_cursor_local(57, 8);
	cout << "Ваш выбор:";
	set_cursor_local(57, 12);
	cout << "Обычный поиск (номер банковской операции)";
	set_cursor_local(57, 13);
	cout << "Расширенный поиск (введите 0)";
	set_cursor_local(57, 14);
	cout << "Поиск:";
	set_cursor_local(57, 41);
	cout << "Номер кнопки в меню:";
}

void Console::interface_myData()
{
	set_cursor_local(34, 0);
	SetConsoleCursorPosition(hConsole, coordinates);
	cout << "МОИ ДАННЫЕ" << endl;
	int y = 0;
	for (int i = 0; i < 11; i++)
	{
		set_cursor_local(2, 1 + y);
		cout << "______________________";
		set_cursor_local(2, 4 + y);
		cout << "______________________";
		set_cursor_local(25, 1 + y);
		cout << "___________________________________________";
		set_cursor_local(25, 4 + y);
		cout << "___________________________________________";
		y = y + 3;
	}

	for (int i = 0; i < 33; i++)
	{
		set_cursor_local(1, 2 + i);
		cout << "|";
		set_cursor_local(24, 2 + i);
		cout << "|";
		set_cursor_local(68, 2 + i);
		cout << "|";
	}
	set_cursor_local(3, 3);
	cout << "1 - логин";
	set_cursor_local(3, 6);
	cout << "2 - пароль";
	set_cursor_local(3, 9);
	cout << "3 - имя";
	set_cursor_local(3, 12);
	cout << "4 - фамилия";
	set_cursor_local(3, 15);
	cout << "5 - возраст";
	set_cursor_local(3, 18);
	cout << "6 - номер телефона";
	set_cursor_local(3, 21);
	cout << "7 - электронная почта";
	set_cursor_local(3, 24);
	cout << "8 - гражданство";
	set_cursor_local(3, 27);
	cout << "9 - город проживания";
	set_cursor_local(3, 30);
	cout << "10 - номер карты";
	set_cursor_local(3, 33);
	cout << "11 - любимый фильм";
	set_cursor_local(1, 36);
	cout << "Внести изменения? (Если да, то нажмите цифру, которая соответствует выбранному Вами полю, в противном случае нажмите 0)";
}

void Console::interface_operation(int operation)
{
	switch (operation)
	{
	case 1:
	{
		set_cursor_local(34, 0);
		cout << "ПОПОЛНЕНИЕ БАНКОВСКОЙ КАРТЫ";
		set_cursor_local(1, 1);
		cout << "Для уверенности, что Вас не взломали, ответьте на вопрос (Ваш любимый фильм?):";

		for (int i = 0; i < 9; i++)
		{
			set_cursor_local(1, 3 + i);
			cout << "|";
			set_cursor_local(37, 3 + i);
			cout << "|";
			set_cursor_local(53, 3 + i);
			cout << "|";
		}
		int y = 0;
		for (int i = 0; i < 4; i++)
		{
			set_cursor_local(2, 2 + y);
			cout << "___________________________________";
			set_cursor_local(38, 2 + y);
			cout << "_______________";
			y = y + 3;
		}
		set_cursor_local(4, 4);
		cout << "Баланс на карте в данный момент";
		set_cursor_local(4, 7);
		cout << "Сумма к зачислению";
		set_cursor_local(4, 10);
		cout << "Баланс на карте после зачисления";
		break;
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
		set_cursor_local(37, 0);
		cout << "ОТКРЫТИЕ ВКЛАДА";
		set_cursor_local(1, 1);
		cout << "Для уверенности, что Вас не взломали, ответьте на вопрос (Ваш любимый фильм?):";
		set_cursor_local(1, 2);
		cout << "Вклад №1";
		for (int i = 0; i < 9; i++)
		{
			set_cursor_local(1, 4 + i);
			cout << "|";
			set_cursor_local(45, 4 + i);
			cout << "|";
			set_cursor_local(61, 4 + i);
			cout << "|";
		}
		int y = 0;
		for (int i = 0; i < 4; i++)
		{
			set_cursor_local(2, 3 + y);
			cout << "___________________________________________";
			set_cursor_local(46, 3 + y);
			cout << "_______________";
			y = y + 3;
		}
		set_cursor_local(4, 5);
		cout << "Название вклада";
		set_cursor_local(47, 5);
		cout << "Щедрый";
		set_cursor_local(4, 8);
		cout << "Процентная ставка";
		set_cursor_local(47, 8);
		cout << "30";
		set_cursor_local(4, 11);
		cout << "Количество дней для зачисления процентов";
		set_cursor_local(47, 11);
		cout << "1095 (3 года)";
		set_cursor_local(1, 14);
		cout << "Вклад №2";
		for (int i = 0; i < 9; i++)
		{
			set_cursor_local(1, 16 + i);
			cout << "|";
			set_cursor_local(45, 16 + i);
			cout << "|";
			set_cursor_local(61, 16 + i);
			cout << "|";
		}
		y = 0;
		for (int i = 0; i < 4; i++)
		{
			set_cursor_local(2, 15 + y);
			cout << "___________________________________________";
			set_cursor_local(46, 15 + y);
			cout << "_______________";
			y = y + 3;
		}
		set_cursor_local(4, 17);
		cout << "Название вклада";
		set_cursor_local(47, 17);
		cout << "Быстрый";
		set_cursor_local(4, 20);
		cout << "Процентная ставка";
		set_cursor_local(47, 20);
		cout << "10";
		set_cursor_local(4, 23);
		cout << "Количество дней для зачисления процентов";
		set_cursor_local(47, 23);
		cout << "182 (Полгода)";
		set_cursor_local(1, 26);
		cout << "Вклад №3";
		for (int i = 0; i < 9; i++)
		{
			set_cursor_local(1, 28 + i);
			cout << "|";
			set_cursor_local(45, 28 + i);
			cout << "|";
			set_cursor_local(61, 28 + i);
			cout << "|";
		}
		y = 0;
		for (int i = 0; i < 4; i++)
		{
			set_cursor_local(2, 27 + y);
			cout << "___________________________________________";
			set_cursor_local(46, 27 + y);
			cout << "_______________";
			y = y + 3;
		}
		set_cursor_local(4, 29);
		cout << "Название вклада";
		set_cursor_local(47, 29);
		cout << "Легкий";
		set_cursor_local(4, 32);
		cout << "Процентная ставка";
		set_cursor_local(47, 32);
		cout << "5";
		set_cursor_local(4, 35);
		cout << "Количество дней для зачисления процентов";
		set_cursor_local(47, 35);
		cout << "365 (Год)";
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

void Console::interface_local_operation()
{
	system("cls");
	set_cursor_local(34, 0);
	cout << "ОТКРЫТИЕ ВКЛАДА";
	for (int i = 0; i < 15; i++)
	{
		set_cursor_local(1, 2 + i);
		cout << "|";
		set_cursor_local(45, 2 + i);
		cout << "|";
		set_cursor_local(61, 2 + i);
		cout << "|";
	}
	int y = 0;
	for (int i = 0; i < 6; i++)
	{
		set_cursor_local(2, 1 + y);
		cout << "___________________________________________";
		set_cursor_local(46, 1 + y);
		cout << "_______________";
		y = y + 3;
	}
	set_cursor_local(4, 3);
	cout << "Баланс на карте в данный момент";
	set_cursor_local(4, 6);
	cout << "Сумма вклада";
	set_cursor_local(4, 9);
	cout << "Баланс на карте после открытия вклада";
	set_cursor_local(4, 12);
	cout << "Сумма доходов";
	set_cursor_local(4, 15);
	cout << "Баланс по окончании срока депозита";
}

void Console::interface_backgroud_topic_partially(int choise)
{
	if (choise == 1)
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)(2 << 4 | 15));
	}
	if (choise == 2)
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)(11 << 4 | 0));
	}
}

void Console::color(int bg, int text)
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD) (bg << 4 | text));
}

void Console::set_cursor_local(int x, int y)
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(hConsole, coordinates);
}