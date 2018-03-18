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
	string text;
public:
	TextEditor() { x = 0; y = 0; }

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
	void setLine()
	{
		char mode;
		text = "";
		int counter = 0;
		for (counter = 0; counter < length; counter++)
		{
			mode = _getch();
			text += mode;
			cout << text;
		}
	}

};

int main()
{
	setlocale(LC_ALL, "Russian");
	int k = 1;
	int X = 0;
	int Y = 0;
	int _length = 0;
	TextEditor Line;
	cout << "¬ведите длину строки :" << endl;
	cin >> _length;
	Line.Setlength(_length);
	cout << "¬ведите координаты X:" << endl;
	cin >> X;
	cout << "¬ведите координаты Y:" << endl;
	cin >> Y;
	system("cls");
	Line.TheCoordinates(X, Y);
	cout << "¬ведите строку длины: ";
	Line.Getlength();
	Line.setLine();
	system("pause");
	system("cls");
}