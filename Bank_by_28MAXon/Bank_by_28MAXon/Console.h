#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;

// Класс для работы с пользовательским интерфейсом
class Console
{
private:
	HANDLE hConsole;
	COORD coordinates;
public:
	Console() {}
	~Console() {}

	void interface_backgroud_topic(int choise); // Выбор фоновой темы
	void interface_start_page(); // Начальная страница
	void interface_input(); // Страница входа в аккаунт
	void interface_registration(); // Страница регистрации
	void interface_confirm(); // Подтверждение регистрации
	void interface_account(int choice_page); // Личный кабинет пользователя
	void interface_menu_main_page();
	void interface_operation();
	void interface_myData();
	void interface_backgroud_topic_partially(int choise); // Выбор частичной фоновой темы
	void color(int bg, int text); // Изменение цвета фона и текста в определенных случаях
	void set_cursor_local(int x, int y); // Установка курсора в определнном месте, заданном по координатам
};