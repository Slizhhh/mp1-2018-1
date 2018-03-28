#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <conio.h>

using namespace std;

class TextEditor {
private:
	int x;
	int y;
	int length;
	char *string;;

public:

	TextEditor()
	{
		length = 1;
		string = new char[length];
	}

	TextEditor(int X, int Y) {
		x = X;
		y = Y;
	}

	TextEditor & operator =(const TextEditor& obj)
	{
		x = obj.x;
		y = obj.y;
		length = obj.length;
	}
	void Setlength(int _length)
	{
		length = _length;
	}
	int Getlength()
	{
		return length;
	}

	void TheCoordinates(int _x, int _y)
	{
		x = _x;
		y = _y;
		for (int j = 0; j < y; j++)
		{
			cout << endl;
		}
		for (int i = 0; i < x; i++)
		{
			cout << " ";
		}
	}

	void SetString()
	{
		for (int i = 0; i < length; i++)
		{
			string[i] = _getch();
			putchar(string[i]);
		}
	}

	char* GetString()
	{
		return string;
	}

	~TextEditor()
	{
		delete[]string;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	int X = 0;
	int Y = 0;
	int _length = 0;
	char* word = nullptr;
	TextEditor Line;
	cout << "¬ведите длину строки : ";
	cin >> _length;
	Line.Setlength(_length);
	cout << "¬ведите координаты X: ";
	cin >> X;
	cout << "¬ведите координаты Y: ";
	cin >> Y;
	system("cls");
	cout << "¬ведите строку длины " << Line.Getlength() << ": ";
	Line.SetString();
	system("pause");
	system("cls");
	Line.TheCoordinates(X, Y);
	cout << Line.GetString() << endl;
	system("pause");
	system("cls");
}