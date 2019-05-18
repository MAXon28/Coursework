#pragma once
#include "Account.h"

// Класс для логики приложения
class Logic
{
private:
	// Переменные для обычного подсчета денег
	unsigned long int new_cash;
	unsigned long int result;
	
	// Переменные для вклада и кредита
	unsigned long int S; // Сумма денежных средств, причитающихся к возврату вкладчику по окончании срока депозита или общая сумма погашения кредита 
	float I; // Годовая процентная ставка
	int t; // Количество дней начисления процентов по привлеченному вкладу
	const int K = 365; // Количество дней в календарном году
	unsigned long int Sp; // Сумма процентов (доходов)
	unsigned long int months_of_credit; // Ежемесячные выплаты
	int number_months; // Срок кредита (в месяцах)

public:
	Logic() {}
	Logic(float percent, int count_days);
	Logic(float percent) : I(percent) {}
	~Logic() {}
	friend istream& operator>>(istream& in, Logic& logic);
	unsigned long int operations(int number_of_operation, unsigned long int now_cash, bool confirm, string name_of_file);
	unsigned long int amount_of_income();
	unsigned long int amount_all_return();
	void return_cash_of_deposit(unsigned long int return_to_card, string name);
	unsigned long int monthly_payment(int months);
	unsigned long int all_payment();
	unsigned long int loan_repayment(unsigned long int all_money_credit);
	vector <string> normal_search(vector <string>& search_history, string word);
	vector <string> advanced_search(vector <string>& advanced_search_history, string name_operation, string cash, string day);
	vector <string> advanced_search(vector <string>& advanced_search_history, string name_operation, string cash, string day, string name_or_number_phone);
	string number_operation_to_name_operation(int number_operation);
	string number_day_to_name_day(string number_day);
	bool checking(int number_of_credit);
	Logic& operator=(const Logic log);
	float degree_for_credit(float number, int months);
	void set_new_cash(unsigned long int number);
	friend ostream& operator<<(ostream& out, Logic& logic);
};