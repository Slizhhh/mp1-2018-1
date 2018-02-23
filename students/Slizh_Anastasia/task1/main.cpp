#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <time.h>

void Enter(int &_hour, int &_min, int &_sec)
{
	cout << "������� ����: ";
	cin >> _hour;
	if ((_hour > 23) || (_hour<0))
	{
		cout << "������";
		return;
	}
	cout << "������� ������: ";
	cin >> _min;
	if ((_min > 59) || (_min<0))
	{
		cout << "������";
		return;
	}
	cout << "������� �������: ";
	cin >> _sec;
	if ((_sec > 59) || (_sec<0))
	{
		cout << "������";
		return;
	}
}

using namespace std;
class Time {
private:
	int hour, minute, second;
public:
	Time(int _hour = 0, int _min = 0, int _sec = 0);
	void showTime();
	void timeDiff(int &_hour, int &_min, int &_sec);
	void getTime(int &, int &, int &);
	void changeTime1(int _hour, int _min, int _sec);
	void changeTime2(int _hour, int _min, int _sec);
	Time & operator=(const Time& obj) {
		hour = obj.hour;
		minute = obj.minute;
		second = obj.second;
		return *this;
	}
};

int main() {
	setlocale(LC_ALL, "rus");
	int k = 0, choice, choice1;
	int _h = 0, _min = 0, _sec = 0;
	int h = 0, min = 0, sec = 0;
	Time T1;
	system("cls");
	cout << "������ �����:" << endl;
	Enter(_h, _min, _sec);
	system("pause");
	system("cls");


	while (k != 3) {
		system("cls");
		cout << "������� �����: ";
		cout << _h << ":" << _min << ":" << _sec << endl;
		cout << "1. ���������� ������� ����� �������� � ��������" << endl;
		cout << "2 ����� �����������" << endl;
		cout << "3. �����" << endl;
		cout << "��� �����: ";
		cin >> choice;
		switch (choice) {
		case 1:
		{
			Enter(h, min, sec);
			T1.timeDiff(h, min, sec);
			cout << "������� ����� �������� � �������� ";
			cout << h << ":" << min << ":" << sec << endl;
			system("pause");
			break;
		}
		case 2:
		{
			cout << "������� ����� ������� �� ������ ��������" << endl << endl;
			Enter(_h, _min, _sec);
			cout << "������� �����������" << endl;
			cout << "1. ������" << endl;
			cout << "2. �����" << endl;
			cout << "��� �����: ";
			cin >> choice1;
			switch (choice1) {
			case 1:
			{
				T1.changeTime1(_h, _min, _sec);
			}
			case 2:
			{
				T1.changeTime2(_h, _min, _sec);
			}
			break;
			}
		}
		case 3:
		{
			return;
		}
		}
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
