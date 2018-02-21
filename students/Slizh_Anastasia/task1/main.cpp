#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <stdio.h>

using namespace std;

void DataTime(int *second, int *minute, int *hour);
class Time
{
private:
	int second = 0;
	int minute = 0;
	int hour = 0;
public:

	void SpecifiedTime()
	{
		cout << "Укажите часы: ";
		cin >> hour;
		if (hour > 24)
		{
			cout << "Ошибка";
			return;
		}
		cout << "Укажите минуты: ";
		cin >> minute;
		if (minute > 60)
		{
			cout << "Ошибка";
			return;
		}
		cout << "Укажите секунды: ";
		cin >> second;
		if (second > 60)
		{
			cout << "Ошибка";
			return;
		}
	}

	void ShowTime()
	{
		cout << "Заданное время: " << hour;
		cout << "." << minute;
		cout << "." << second << endl;
	}
};


int main()
{
	setlocale(LC_ALL, "rus");
	int c = 0;
	Time t;
	while (c != 5)
	{
		cout << "Меню: " << endl;
		cout << "1)Установить время " << endl;
		cout << "2)Узнать время " << endl;
		cout << "3)Узнать разницу между заданным временем и установленным " << endl;
		cout << "4)Сдвинуть время на заданное смещение " << endl;
		cout << "5)Выйти из программы " << endl;
		cin >> c;
		switch (c)
		{
		case 1:
		{
			t.SpecifiedTime();
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			t.ShowTime();
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
		}
		}//switch
	}//while
	return 0;
}//int main
