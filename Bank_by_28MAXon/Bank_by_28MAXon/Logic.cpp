#include "pch.h"
#include "Logic.h"


Logic::Logic(float percent, int count_days)
{
	I = percent;
	t = count_days;
}

istream& operator>>(istream& in, Logic& logic)
{
	in >> logic.new_cash;
	return in;
}

unsigned long int Logic::operations(int number_of_operation, unsigned long int now_cash, bool confirm, string name_of_file)
{
	switch (number_of_operation)
	{
	case 1:
	{
		result = 0;
		result = new_cash + now_cash;
		if (confirm == true)
		{
			ifstream file_read(name_of_file + ".txt");
			string file_Data[11];
			for (int i = 0; i < 11; i++)
			{
				file_read >> file_Data[i];
			}
			file_read.close();
			ofstream file_write(name_of_file + ".txt");
			for (int i = 0; i < 12; i++)
			{
				if (i < 11)
				{
					file_write << file_Data[i] << endl;
				}
				else
				{
					file_write << result;
				}
			}
			file_write.close();
		}
		return result;
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
		if (confirm == true)
		{
			ifstream file_read(name_of_file + ".txt");
			string file_Data[11];
			for (int i = 0; i < 11; i++)
			{
				file_read >> file_Data[i];
			}
			file_read.close();
			ofstream file_write(name_of_file + ".txt");
			for (int i = 0; i < 12; i++)
			{
				if (i < 11)
				{
					file_write << file_Data[i] << endl;
				}
				else
				{
					file_write << now_cash;
				}
			}
			file_write.close();
		}
		else
		{
			result = 0;
			result = now_cash - new_cash;
		}
		return result;
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

unsigned long int Logic::amount_of_income()
{
	Sp = (new_cash * I * t) / (K * 100);
	return Sp;
}

unsigned long int Logic::amount_all_return()
{
	S = new_cash + Sp;
	return S;
}

vector<string> Logic::normal_search(vector <string>& search_history, string word)
{
	int count_string;
	count_string = search_history.size();
	int i = 0;
	int dot = 0;
	bool searching = false;
	do
	{
		while (search_history[i] != "новая операция")
		{
			if (search_history[i + 1] == "новая операция")
			{
				if (search_history[i] == word)
				{
					searching = true;
				}
			}
			i++;
		}
		if (searching == true)
		{
			i++;
			dot = i;
			searching = false;
		}
		else
		{
			int j = dot;
			int count_delete = 0;
			while (search_history[j] != "новая операция")
			{
				auto iterator = search_history.cbegin();
				search_history.erase(iterator + j);
				count_string--;
				search_history.resize(count_string);
				if (count_string == 0)
				{
					break;
				}
				count_delete++;
			}
			auto iterator = search_history.cbegin();
			search_history.erase(iterator + j);
			count_delete++;
			count_string--;
			i = i - count_delete + 1;
		}
		if (i == search_history.size())
		{
			break;
		}
	} while (i != search_history.size());
	return search_history;
}

vector <string> Logic::advanced_search(vector <string>& advanced_search_history, string name_operation, string cash, string day)
{
	int count_string;
	count_string = advanced_search_history.size();
	int i = 0;
	int dot = 0; // сюда буду подавать элемент, на котором закончились данные об одной операции
	bool searching = false;
	do
	{
		while (advanced_search_history[i] != "новая операция")
		{
			if (advanced_search_history[i + 1] == "новая операция")
			{
				if (advanced_search_history[i] == name_operation)
				{
					if (advanced_search_history[i - 3] == cash)
					{
						if (advanced_search_history[i - 2] == day)
						{
							searching = true;
						}
						else
						{
							searching = false;
						}
					}
					else
					{
						searching = false;
					}
				}
				else
				{
					searching = false;
				}
			}
			i++;
		}
		if (searching == false)
		{
			int j = dot;
			int count_delete = 0;
			while (advanced_search_history[j] != "новая операция")
			{
				auto iterator = advanced_search_history.cbegin();
				advanced_search_history.erase(iterator + j);
				count_string--;
				advanced_search_history.resize(count_string);
				count_delete++;
				if (count_string == 0)
				{
					break;
				}
			}
			auto iterator = advanced_search_history.cbegin();
			count_delete++;
			advanced_search_history.erase(iterator + j);
			count_string--;
			advanced_search_history.resize(count_string);
			i = i - count_delete + 1;
		}
		if (searching == true)
		{
			i++;
			dot = i;
		}
	} while (i < advanced_search_history.size());
	return advanced_search_history;
}

string Logic::number_operation_to_name_operation(int number_operation)
{
	switch (number_operation)
	{
	case 0:
	{
		return "0";
		break;
	}
	case 1:
	{
		return "ПОПОЛНЕНИЕ БАНКОВСКОЙ КАРТЫ";
		break;
	}
	case 2:
	{
		return "ПЕРЕВОД КЛИЕНТУ НАШЕГО БАНКА";
		break;
	}
	case 3:
	{
		return "ПЕРЕВОД КЛИЕНТУ ДРУГОГО БАНКА";
		break;
	}
	case 4:
	{
		return "ОПЛАТА СОТОВОЙ СВЯЗИ";
		break;
	}
	case 5:
	{
		return "ОТКРЫТИЕ ВКЛАДА";
		break;
	}
	case 6:
	{
		return "ПОЛУЧЕНИЕ КРЕДИТА";
		break;
	}
	case 7:
	{
		return "ПОГАШЕНИЕ КРЕДИТА";
		break;
	}
	}
	return "0";
}

string Logic::number_day_to_name_day(string number_day)
{
	int number;
	number = stoi(number_day);
	switch (number)
	{
	case 1:
	{
		return "Понедельник";
		break;
	}
	case 2:
	{
		return "Вторник";
		break;
	}
	case 3:
	{
		return "Среда";
		break;
	}
	case 4:
	{
		return "Четверг";
		break;
	}
	case 5:
	{
		return "Пятница";
		break;
	}
	case 6:
	{
		return "Суббота";
		break;
	}
	case 7:
	{
		return "Воскресенье";
		break;
	}
	}
}

Logic& Logic::operator=(const Logic log)
{
	new_cash = log.new_cash;
	result = log.result;
	return *this;
}

ostream& operator<<(ostream& out, Logic& logic)
{
	out << logic.new_cash;
	return out;
}