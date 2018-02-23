#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <time.h>

using namespace std;
void Enter(int *_h, int *_min, int *_sec);
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
	void timeDiff(int _hour, int _minute, int _second);
	void changeTime1(int _hour, int _minute, int _second);
	void changeTime2(int _hour, int _minute, int _second);
};

int main() {
	setlocale(LC_ALL, "rus");
	int k = 0, choice, choice1, p;
	int _h = 0, _min = 0, _sec = 0;
	system("cls");
	Time T1;
	cout << "������ �����" << endl;
	Enter(&_h, &_min, &_sec);

	system("pause");
	system("cls");


	while (k != 3) {
		system("cls");
		cout << "�������� �����: ";
		cout << hous << ":" << minute << ":" << second << endl;
		system("pause");
		cout << "1. ���������� ������� ����� �������� � ��������" << endl;
		cout << "2  �������� �����" << endl;
		cout << "3. �����" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
		{
			Enter(&_h, &_min, &_sec);
			T1.timeDiff(_h, _min, _sec);
			cout << "������� ����� �������� � �������� ";
			cout << _h << ":" << _min << ":" << _sec << endl;
			system("pause");
			break;
		}
		case 2:
		{
			cout << "������� ����� ������� �� ������ ��������" << endl << endl;
			Enter(&_h, &_min, &_sec);
			while (p != 3)
			{
				cout << "������� �����������" << endl;
				cout << "1. ������" << endl;
				cout << "2. �����" << endl;
				cout << "3. ����� � ������� ����" << endl;
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
				case 3: {
					p = 3; }
				}
				system("cls");
			}
			return;
		case 3:
		{
			return 0;
		}
		}
		}
	}
}

void Enter(int *h, int *min, int *sec)
{
	cout << "������� ����: ";
	cin >> *h;
	if ((*h > 23) || (*h<0))
	{
		cout << "������";
		return 0;
	}
	cout << "������� ������: ";
	cin >> *min;
	if ((*min > 59) || (*min<0))
	{
		cout << "������";
		return 0;
	}
	cout << "������� �������: ";
	cin >> *sec;
	if ((*sec > 59) || (*sec<0))
	{
		cout << "������";
		return 0;
	}
}

void Time::timeDiff(int *_hour, int *_minute, int *_second)
{
	int second1 = hour * 3600 + minute * 60 + second;
	int second2 = *_hour * 3600 + *_minute * 60 + *_second; 3
		int diff = abs(second1 - second2);
	*_hour = diff / 3600;
	diff = diff - *_hour * 3600;
	*_minute = diff / 60;
	*_second = diff % 60;
}

void Time::changeTime1(int _hour, int _minute, int _second)
{
	hour -= _hour;
	minute -= _minute;
	second -= _second;
	cout << hour << ":" << minute << ":" << second << endl;
}

void Time::changeTime2(int _hour, int _minute, int _second)
{
	hour -= _hour;
	minute -= _minute;
	second -= _second;
	cout << hour << ":" << minute << ":" << second << endl;
}
