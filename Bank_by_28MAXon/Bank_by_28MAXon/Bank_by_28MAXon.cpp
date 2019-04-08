#include "pch.h"
#include <iostream>
#include <locale.h>
#include <string>
#include "Account.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "\t\t\t\t\tБанк!\n________________________________________________________________________________\n"; 
	cout << " - Вход в личный кабинет\n - Создание учётной записи клиента\n";
	cout << "________________________________________________________________________________\n";
	cout << " Для входа в личный кабинет нажмите цифру 1\n Для регистрации в банке нажмите 2\n Ваш выбор:";
	account men;
	int change;
	cin.ignore() >> change;
	switch (change)
	{
		case 1:
		{
			
		}
	}
	system("pause");

}
