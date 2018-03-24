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
	char *string;

public:

	TextEditor()
	{
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

	TextEditor& operator=(TextEditor &obj1)
	{
		if (this == &obj1)
			return *this;
		else
			if (length != obj1.length)
			{
				delete[] string;
				string = new char[obj1.length + 1];
			}
		strcpy(string, obj1.string);
		length = obj1.length;
		return *this;
	}

	TextEditor(const TextEditor &obj2)
	{
		length = obj2.length;
		string = new char[length + 1];
		strcpy(string, obj2.string);
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

	void SetString(char* word)
	{
		length = strlen(word);
		string = new char[length + 1];
		strcpy(string, word);
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
	cin >> word;
	Line.SetString(word);
	system("pause");
	system("cls");
	Line.TheCoordinates(X, Y);
	cout << Line.GetString() << endl;
	system("pause");
	system("cls");
}