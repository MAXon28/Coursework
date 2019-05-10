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
	void interface_menu(int choice_page); // Личный кабинет пользователя
	void interface_main_page(); // Главная страничка
	void interface_operations_page(); // Страничка банковских операций (вторая)
	void interface_history_page();
	void interface_myData(); // Страничка для изменения моих данных
	void interface_operation(int operation); // Страничка выбранной банковской операции
	void interface_backgroud_topic_partially(int choise); // Выбор частичной фоновой темы
	void color(int bg, int text); // Изменение цвета фона и текста в определенных случаях
	void set_cursor_local(int x, int y); // Установка курсора в определнном месте, заданном по координатам
};