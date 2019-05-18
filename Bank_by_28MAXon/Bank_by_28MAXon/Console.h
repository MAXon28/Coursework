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
	void interface_main_page(); // Главная страница
	void interface_operations_page(); // Страница банковских операций (вторая)
	void interface_history_page(); // Страница с историями банковских операций клиента (третья)
	void interface_exit_page(); // Страница выхода
	void interface_myData(); // Страница для изменения моих данных
	void interface_myTheme(); // Страница для изменения фона
	void interface_operation(int operation); // Страница выбранной банковской операции
	void interface_local_operation(int choice);
	void interface_backgroud_topic_partially(int choise); // Выбор частичной фоновой темы
	void color(int bg, int text); // Изменение цвета фона и текста в определенных случаях
	void set_cursor_local(int x, int y); // Установка курсора в определнном месте, заданном по координатам
};