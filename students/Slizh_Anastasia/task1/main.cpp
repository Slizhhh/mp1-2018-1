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
		cout << "������� ����: ";
		cin >> hour;
		if (hour > 24)
		{
			cout << "������";
			return;
		}
		cout << "������� ������: ";
		cin >> minute;
		if (minute > 60)
		{
			cout << "������";
			return;
		}
		cout << "������� �������: ";
		cin >> second;
		if (second > 60)
		{
			cout << "������";
			return;
		}
	}

	void ShowTime()
	{
		cout << "�������� �����: " << hour;
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
		cout << "����: " << endl;
		cout << "1)���������� ����� " << endl;
		cout << "2)������ ����� " << endl;
		cout << "3)������ ������� ����� �������� �������� � ������������� " << endl;
		cout << "4)�������� ����� �� �������� �������� " << endl;
		cout << "5)����� �� ��������� " << endl;
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
