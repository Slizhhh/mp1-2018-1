#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>

using namespace std;

struct Date {
	int day;
	int month;
	int year;
	double wt;
	Date() { day = 0; month = 0; year = 0;  wt = 0; }

	Date & operator=(const Date &date)
	{
		day = date.day;
		month = date.month;
		year = date.year;
		wt = date.wt;
		return *this;
	}
};

ofstream scale_in;
ifstream scale_out;

ostream &operator<<(ostream& date, const Date &obj)
{
	date << obj.day << '.' << obj.month << '.' << obj.year;
	return date;
}

class Scale
{
	Date *DataWT;
	string _name;
	int size = 0;  // кол-во строк в структуре дата

public:

	Scale()
	{
		_name = "new";
		DataWT = nullptr;
	}


	Scale& operator=(const Scale &sc)//
	{
		size = sc.size;
		_name = sc._name;
		DataWT = new Date[size];
		for (int i = 0; i < size; i++)
		{
			DataWT[i] = sc.DataWT[i];
		}
		return *this;
	}


	void SetName(string name, int nomer)
	{
		if (nomer < 5)
		{
			_name = name;
		}
		else {
			cout << "Достигнуто максимальное колличество пользователей";
		}
	}

	string getname()
	{
		return _name;
	}

	void SetStartData(int _day, int _month, int _year)
	{
		DataWT = new Date[1];
		DataWT[0].day = _day;
		DataWT[0].month = _month;
		DataWT[0].year = _year;
		DataWT[0].wt = 0;
	};


	void GetStartData()
	{
		cout << DataWT[0].day << "." << DataWT[0].month << "." << DataWT[0].year << endl;
	}

	void AddStruct() // добавим новую память в массив струкуры
	{
		Date *temp;
		temp = new Date[size + 1];
		for (int i = 0; i <= size; i++)
		{
			temp[i] = DataWT[i];
		}
		delete[](DataWT);
		DataWT = new Date[size + 2];
		for (int i = 0; i <= size; i++)
		{
			DataWT[i] = temp[i];
		}
		delete[]temp;
		size++;
	}

	void SetNewMon(int _day, int _month, int _year, double _wt)
	{
		AddStruct();
		DataWT[size].day = _day;
		DataWT[size].month = _month;
		DataWT[size].year = _year;
		DataWT[size].wt = _wt;
	}

	void getSize()
	{
		cout << "Всего было измерений - " << size << endl;
	}

	void GetData(int i)
	{
		//if (i>=0 && i<=size) {
		cout << DataWT[i].day << "." << DataWT[i].month << "." << DataWT[i].year << " Вес -" << DataWT[i].wt << endl;

	}

	double AverageWT(int _month, int _year) {
		double av_wt = 0;

		for (int i = 0; i <= size; i++)
		{
			if ((DataWT[i].month == _month) && (DataWT[i].year == _year))
			{
				av_wt += DataWT[i].wt;
			}
		}
		av_wt /= size;
		return av_wt;
	}

	double AllAverageWT() {
		double av_wt = 0;
		for (int i = 0; i <= size; i++)
		{
			av_wt += DataWT[i].wt;
		}
		av_wt /= size;
		return av_wt;
	}

	double MinWT(int _month, int _year) {
		double min_wt = 0;
		for (int i = 1; i < size; i++)
		{
			if ((DataWT[i].month == _month) && (DataWT[i].year == _year))
			{
				if (DataWT[i].wt < DataWT[i + 1].wt)
					min_wt = DataWT[i].wt;
				else
					min_wt = DataWT[i + 1].wt;
			}
		}
		return min_wt;
	}

	double AllMinWT() {
		double min_wt = 0;
		for (int i = 1; i < size; i++)
		{
			if (DataWT[i].wt < DataWT[i + 1].wt)
				min_wt = DataWT[i].wt;
			else
				min_wt = DataWT[i + 1].wt;
		}
		return min_wt;
	}

	double MaxWT(int _month, int _year) {
		double max_wt = 0;
		for (int i = 1; i < size; i++)
		{
			if ((DataWT[i].month == _month) && (DataWT[i].year == _year))
			{
				if (DataWT[i].wt > DataWT[i + 1].wt)
					max_wt = DataWT[i].wt;
				else
					max_wt = DataWT[i + 1].wt;
			}
		}
		return max_wt;
	}

	double AllMaxWT() {
		double max_wt = 0;
		for (int i = 1; i < size; i++)
		{
			if (DataWT[i].wt > DataWT[i + 1].wt)
				max_wt = DataWT[i].wt;
			else
				max_wt = DataWT[i + 1].wt;
		}
		return max_wt;
	}

	void SaveInFile()
	{
		scale_in << _name << endl;
		scale_in << "Количество наблюдений: " << size << endl;
		for (int i = 0; i < size; i++)
		{
			scale_in << DataWT[i] << endl;
		}
	}

	void LoadFromFile()
	{
		char str[100];
		scale_out.getline(str, 100, '\n');
		_name = str;
		scale_out.getline(str, 80, ' ');
		size = atoi(str);
		DataWT = new Date[size];
		for (int i = 0; i < size; i++)
		{
			scale_out.getline(str, 20, '.');
			DataWT[i].day = atoi(str);
			scale_out.getline(str, 20, '.');
			DataWT[i].month = atoi(str);
			scale_out.getline(str, 20, '\n');
			DataWT[i].year = atoi(str);
			scale_out.getline(str, 20, '\n');
			DataWT[i].wt = atoi(str);
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Date data;
	string Name;
	int coince = 0;
	int counter = 10;
	double _wt;
	int _day, _month, _year;
	int nomer = 0;
	Scale Mysc[5];
	while (coince != 14)
	{
		cout << "1)Добавить пользователя" << endl;
		cout << "2)Выбрать существуюший пользователь" << endl;
		cout << "3)Установить начальную дату наблюдения" << endl;
		cout << "4)Задать нааблюдение" << endl;
		cout << "5)Узнать вес в выбранном наблюдении" << endl;
		cout << "6)Средний вес в одном месяце" << endl;
		cout << "7)Средний вес за всю историю наблюдений" << endl;
		cout << "8)Минимальный вес за месяце" << endl;
		cout << "9)Минимальный вес за всю историю наблюдений" << endl;
		cout << "10)Максимальный вес за месяце" << endl;
		cout << "11)Максимальный вес за всю историю наблюдений" << endl;
		cout << "12)Сохранить историю наблюдений в файл" << endl;
		cout << "13)Считать историю наблюдений из файла" << endl;
		cout << "14)Выход" << endl;
		cin >> coince;
		switch (coince)
		{
		case 1:
		{
			cout << "Введите имя: ";
			cin >> Name;
			Mysc[nomer].SetName(Name, nomer);
			nomer++;
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			if (nomer == 0)
			{
				cout << "Необходимо добавить пользователя" << endl;
				system("pause");
				break;
			}
			cout << "Введите имя: ";
			cin >> Name;
			string tt;
			int i = 0;
			while (i < 5)
			{
				if (Name == Mysc[i].getname())
				{
					cout << "Выбран пользователь: " << Mysc[i].getname() << endl;
					counter = i;
					break;
				}
				i++;
			}
			if (counter == 10) { cout << "Такое имя не найдено" << endl; }

			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			if (nomer == 0)
			{
				cout << "Необходимо добавить пользователя" << endl;
				system("pause");
				break;
			}
			cout << "Пользователь " << Mysc[counter].getname() << endl;
			cout << "Введите начальную дату наблюдений:" << endl;
			cout << "День- ";
			cin >> _day;
			cout << "месяц- ";
			cin >> _month;
			cout << "год- ";
			cin >> _year;
			cout << "Введите вес";
			Mysc[counter].SetStartData(_day, _month, _year);
			break;
		}
		case 4:
		{
			if (nomer == 0)
			{
				cout << "Необходимо добавить пользователя" << endl;
				system("pause");
				break;
			}
			cout << "Пользователь " << Mysc[counter].getname() << endl;
			cout << "Наблюдение начинается с ";
			Mysc[counter].GetStartData();
			cout << "Введите следующее значение" << endl;
			cout << "Введите День: ";
			cin >> _day;
			cout << "Введите номер месяца: ";
			cin >> _month;
			cout << "Введите год: ";
			cin >> _year;
			cout << "Введите значение веса(кг): ";
			cin >> _wt;
			Mysc[counter].SetNewMon(_day, _month, _year, _wt);
			break;
		}
		case 5:
		{
			if (nomer == 0)
			{
				cout << "Необходимо добавить пользователя" << endl;
				system("pause");
				break;
			}
			cout << "Пользователь " << Mysc[counter].getname() << endl;
			Mysc[counter].getSize();
			cout << "Выберете номер наблюдения" << endl;
			cin >> _day;
			Mysc[counter].GetData(_day);
			system("pause");
			break;
		}
		case 6:
		{
			cout << "Пользователь " << Mysc[counter].getname() << endl;
			cout << "Ведите месяц и год, в котором будет расчитываться средний вес " << endl;
			cout << "Введите номер месяца: ";
			cin >> _month;
			cout << "Введите год: ";
			cin >> _year;
			cout << "Средний вес за этот месяц = " << Mysc[counter].AverageWT(_month, _year) << endl;
			system("pause");
			system("cls");
			break;
		}
		case 7: {
			cout << "Пользователь " << Mysc[counter].getname() << endl;
			cout << "Средний вес за всю историю пользователя - " << Mysc[counter].AllAverageWT() << endl;
			system("pause");
			system("cls");
			break;
		}
		case 8: {
			cout << "Пользователь " << Mysc[counter].getname() << endl;
			cout << "Ведите месяц и год, в котором будет расчитываться минимальный вес" << endl;
			cout << "Введите номер месяца: ";
			cin >> _month;
			cout << "Введите год: ";
			cin >> _year;
			cout << "Минимальный вес за этот месяц = " << Mysc[counter].MinWT(_month, _year) << endl;
			system("pause");
			system("cls");
			break;
		}
		case 9: {
			cout << "Пользователь " << Mysc[counter].getname() << endl;
			cout << "Минимальный вес за всю историю пользователя - " << Mysc[counter].AllMinWT() << endl;
			system("pause");
			system("cls");
			break;
		}
		case 10: {
			cout << "Пользователь " << Mysc[counter].getname() << endl;
			cout << "Ведите месяц и год, в котором будет расчитываться максимальный вес" << endl;
			cout << "Введите номер месяца: ";
			cin >> _month;
			cout << "Введите год: ";
			cin >> _year;
			cout << "Максимальный вес за этот месяц = " << Mysc[counter].MaxWT(_month, _year) << endl;
			system("pause");
			system("cls");
			break;
		}
		case 11: {
			cout << "Пользователь " << Mysc[counter].getname() << endl;
			cout << "Максимальный вес за всю историю пользователя - " << Mysc[counter].AllMaxWT() << endl;
			system("pause");
			system("cls");
		}
		case 12: {
			scale_in.open("scale.txt");
			scale_in << "Количество членов семьи: " << counter << endl;
			for (int i = 0; i < counter; i++)
			{
				Mysc[i].SaveInFile();
			}
			scale_in.close();
			break;
		}
		case 13: {
			char str[20];
			scale_out.open("scale.txt");
			scale_out.getline(str, 20, ' ');
			scale_out.getline(str, 20, ' ');
			scale_out.getline(str, 20, ' ');
			scale_out.getline(str, 20, '\n');
			counter = atoi(str);
			for (int i = 0; i < counter; i++)
			{
				Mysc[i].LoadFromFile();
			}
			scale_out.close();
			break;
		}
		default: {
			cout << "Данной операции не существует";
			break; }
		}//switch
		system("cls");
	}//while
}//main
