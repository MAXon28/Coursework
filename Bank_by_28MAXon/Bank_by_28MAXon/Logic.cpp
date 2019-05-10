#include "pch.h"
#include "Logic.h"

Logic::Logic()
{
}


Logic::~Logic()
{
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
	}
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
		while (search_history[i] != "íîâàÿ îïåğàöèÿ")
		{
			i++;
			if (search_history[i + 1] == "íîâàÿ îïåğàöèÿ")
			{
				if (search_history[i] == word)
				{
					i++;
					if (i == search_history.size())
					{
						searching = true;
						break;
					}
					i++;
				}
				else
				{
					int j = dot;
					auto iterator = search_history.cbegin();
					j++;
					while (search_history[j] != "íîâàÿ îïåğàöèÿ")
					{
						search_history.erase(iterator + j);
						j++;
						count_string--;
						search_history.resize(count_string);
						if (count_string == 0)
						{
							break;
						}
					}
					search_history.erase(iterator + j);
					count_string--;
					searching = false;
				}

			}
			if (searching == true)
			{
				dot = i;
			}
			if (i == search_history.size())
			{
				break;
			}
		}
	} while (i != search_history.size());
	return search_history;
}

vector <string> Logic::advanced_search(vector <string>& advanced_search_history, string name_operation, string cash, string date)
{
	int count_string;
	count_string = advanced_search_history.size();
	int i = 0;
	int dot = 0;
	bool searching = false;
	do
	{
		while (advanced_search_history[i] != "íîâàÿ îïåğàöèÿ")
		{
			i++;
			if (advanced_search_history[i + 1] == "íîâàÿ îïåğàöèÿ")
			{
				if (advanced_search_history[i] == name_operation)
				{
					if (advanced_search_history[i - 3] == cash)
					{
						if (advanced_search_history[i - 2] == date)
						{
							searching = true;
							i++;
						}
						else
						{
							searching = false;
							break;
						}
					}
					else
					{
						searching = false;
						break;
					}
				}
				else
				{
					searching = false;
					break;
				}
			}
		}
		if (searching == false)
		{
			int j = dot;
			auto iterator = advanced_search_history.cbegin();
			j++;
			while (advanced_search_history[j] != "íîâàÿ îïåğàöèÿ")
			{
				advanced_search_history.erase(iterator + j);
				count_string--;
				advanced_search_history.resize(count_string);
				if (count_string == 0)
				{
					break;
				}
			}
			advanced_search_history.erase(iterator + j);
			count_string--;
			i = i + 2;
		}
		if (searching == true)
		{
			dot = i;
			i++;
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
		return "ÏÎÏÎËÍÅÍÈÅ ÁÀÍÊÎÂÑÊÎÉ ÊÀĞÒÛ";
		break;
	}
	case 2:
	{
		return "ÏÅĞÅÂÎÄ ÊËÈÅÍÒÓ ÍÀØÅÃÎ ÁÀÍÊÀ";
		break;
	}
	case 3:
	{
		return "ÏÅĞÅÂÎÄ ÊËÈÅÍÒÓ ÄĞÓÃÎÃÎ ÁÀÍÊÀ";
		break;
	}
	case 4:
	{
		return "ÎÏËÀÒÀ ÑÎÒÎÂÎÉ ÑÂßÇÈ";
		break;
	}
	case 5:
	{
		return "ÎÒÊĞÛÒÈÅ ÂÊËÀÄÀ";
		break;
	}
	case 6:
	{
		return "ÏÎËÓ×ÅÍÈÅ ÊĞÅÄÈÒÀ";
		break;
	}
	case 7:
	{
		return "ÏÎÃÀØÅÍÈÅ ÊĞÅÄÈÒÀ";
		break;
	}
	}
	return "0";
}

ostream& operator<<(ostream& out, Logic& logic)
{
	out << logic.new_cash;
	return out;
}