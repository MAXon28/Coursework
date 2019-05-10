#pragma once
#include "Account.h"

// Класс для логики приложения
class Logic
{
private:
	// Переменные для обычного подсчета денег
	unsigned long int new_cash;
	unsigned long int result;

	// Переменные для вклада
	unsigned long int S; // Сумма денежных средств, причитающихся к возврату вкладчику по окончании срока депозита. Она состоит из первоначальной суммы размещенных денежных средств, плюс начисленные проценты
	float I; // Годовая процентная ставка
	int t; // Количество дней начисления процентов по привлеченному вкладу
	int K; // Количество дней в календарном году
	unsigned long int P; // Первоначальная сумма привлеченных в депозит денежных средств
	unsigned long int Sp; // Сумма процентов (доходов)
public:
	Logic();
	~Logic();

	friend istream& operator>>(istream& in, Logic& logic);
	unsigned long int operations(int number_of_operation, unsigned long int now_cash, bool confirm, string name_of_file);
	vector <string> normal_search(vector <string>& search_history, string word);
	vector <string> advanced_search(vector <string>& advanced_search_history, string name_operation, string cash, string date);
	string number_operation_to_name_operation(int number_operation);

	friend ostream& operator<<(ostream& out, Logic& logic);
};

