#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <time.h>



using namespace std;
void Enter(int *_hour, int *_minute, int *_second);
class Time {
private:
	int hour, minute, second;
public:
	Time(int _hour = 0, int _min = 0, int _sec = 0) {}
	Time & operator=(const Time& obj) {
		hour = obj.hour;
		minute = obj.minute;
		second = obj.second;
		return *this;
	}
	void timeDiff(int &_hour, int &_min, int &_sec);
	void changeTime1(int _hour, int _min, int _sec);
	void changeTime2(int _hour, int _min, int _sec);
};

int main() {
	setlocale(LC_ALL, "rus");
	int k = 0, choice, choice1;
	int _hour = 0, _minute = 0, _second = 0;
	int hour = 0, minute = 0, second = 0;
	Time T1;
	system("cls");
	cout << "Задать время:" << endl;
	Enter(&_hour, &_minute, &_second);
	system("pause");
	system("cls");


	while (k != 3) {
		system("cls");
		cout << "Текущее время: ";
		cout << _hour << ":" << _minute << ":" << _second << endl;
		cout << "1. Рассчитать разницу между введеным и заданным" << endl;
		cout << "2 Время перемещения" << endl;
		cout << "3. Выход" << endl;
		cout << "Ваш выбор: ";
		cin >> choice;
		switch (choice) {
		case 1:
		{
			Enter(&_hour, &_minute, &_second);
			T1.timeDiff(hour, minute, second);
			cout << "Разница между введеным и заданным ";
			cout << hour << ":" << minute << ":" << second << endl;
			system("pause");
			break;
		}
		case 2:
		{
			cout << "Введите время которое вы хотите изменить" << endl << endl;
			Enter(&_hour, &_minute, &_second);
			cout << "Выбрать направление" << endl;
			cout << "1. Вперед" << endl;
			cout << "2. Назад" << endl;
			cout << "Ваш выбор: ";
			cin >> choice1;
			switch (choice1) {
			case 1:
			{
				T1.changeTime1(_hour, _minute, _second);
			}
			case 2:
			{
				T1.changeTime2(_hour, _minute, _second);
			}
			break;
			}
		}
		case 3:
		{
			return 0;
		}
		}
	}
}

void Enter(int &_hour, int &_minute, int &_second)
{
	cout << "Укажите часы: ";
	cin >> _hour;
	if ((_hour > 23) || (_hour<0))
	{
		cout << "Ошибка";
		return;
	}
	cout << "Укажите минуты: ";
	cin >> _minute;
	if ((_minute > 59) || (_minute<0))
	{
		cout << "Ошибка";
		return;
	}
	cout << "Укажите секунды: ";
	cin >> _second;
	if ((_second > 59) || (_second<0))
	{
		cout << "Ошибка";
		return;
	}
}

void Time::timeDiff(int &_hour, int &_minute, int &_second)
{
	int second1 = hour * 3600 + minute * 60 + second;
	int second2 = _hour * 3600 + _minute * 60 + _second;
	int diff = second1 - second2;
	_minute = diff / 60;
	_second = diff - _minute * 60;
	diff = _minute;
	_hour = diff / 60;
	_minute = diff - _hour * 60;
}

void Time::changeTime1(int _hour, int _minute, int _second)
{
	hour -= _hour;
	minute -= _minute;
	second -= _second;
}

void Time::changeTime2(int _hour, int _minute, int _second)
{
	hour -= _hour;
	minute -= _minute;
	second -= _second;
}
