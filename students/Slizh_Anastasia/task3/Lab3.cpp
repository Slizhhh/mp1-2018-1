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
	string setLine(string text)
	{
		return text;
	}

};

int main()
{
	setlocale(LC_ALL, "Russian");
	int X = 0;
	int Y = 0;
	int _length = 0;
	string _text = "";
	char mode;
	TextEditor Line;
	cout << "¬ведите длину строки : ";
	cin >> _length;
	Line.Setlength(_length);
	cout << "¬ведите координаты X: ";
	cin >> X;
	cout << "¬ведите координаты Y: ";
	cin >> Y;
	system("cls");
	cout << "¬ведите строку длины: ";
	for (int counter = 0; counter < _length; counter++)
	{
		mode = _getch();
		_text += mode;
	}
	Line.Getlength();
	Line.TheCoordinates(X, Y);
	Line.setLine(_text);
	system("pause");
	system("cls");
}