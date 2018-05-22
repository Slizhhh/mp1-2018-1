#include <iostream>
#include <time.h> 
#include <stdio.h> 
#include <windows.h> 
#include <conio.h>  

using namespace std;

HANDLE hConsole;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GotoXY(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hStdOut, coord);
}

//Цвет
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Purpur = 5
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 2) | text));
}


class  Snake// структура змейка 
{
public:COORD * t;
public:int PCount;
};
enum uprawlenie { LEFT, UP, RIGHT, DOWN }; //направление змейки
class Game //даные-точности: змейки, яблок, передвижение по X и Y, задержка, направление
{
public:Snake snake; //змейка
public:COORD apple; //яблоко
public:int dx, dy; //передвижение
public:int pause; //задержка
public:int nap; //направление

};


void PlusApple(Game &g) //Функция разброски яблок
{
	int i, x, y;
	int n = g.snake.PCount;
	do
	{
		x = rand() % 56 + 3;
		y = rand() % 19 + 3;
		for (i = 0; i < n; i++)
		{
			if (x == g.snake.t[i].X && y == g.snake.t[i].Y) // проверка чтоб яблоко не бросить на змею
				break;
		}
	} while (i < n);
	g.apple.X = x;
	g.apple.Y = y;
	SetConsoleCursorPosition(hConsole, g.apple);
	SetConsoleTextAttribute(hConsole, 0x0c); //цвет яблока  
	printf("%c", 4);

}


void StartGame(Game &g) // Функця старта змейки ее координат и скорости
{
	system("cls");
	g.snake.PCount = 3; //начальная длина змейки
	g.snake.t = new COORD[3];
	for (int i = 0; i < 3; i++)
	{
		g.snake.t[i].X = 20 + i;
		g.snake.t[i].Y = 20;

	}
	g.dx = 1;
	g.dy = 0;
	g.pause = 100;//скорость передвижение змеи
	PlusApple(g);//рисуем яблока
}

void _STENA()
{
	SetColor(Cyan, Black);
	GotoXY(64, 2); cout << "Данные:" << endl;
	GotoXY(64, 3); cout << "Собрано яблок:0" << endl;
	GotoXY(64, 4); cout << "Длина змейки:3" << endl;
	GotoXY(64, 8); cout << "Esc:Выход" << endl;
	GotoXY(64, 9); cout << "P:Пауза" << endl;
	GotoXY(64, 7); cout << "Управление:" << endl;
	GotoXY(64, 13); printf("%c", 24); cout << ":Вверх" << endl;
	GotoXY(64, 14); printf("%c", 25); cout << ":Вниз" << endl;
	GotoXY(64, 15); printf("%c", 27); cout << ":Влево" << endl;
	GotoXY(64, 16); printf("%c", 26); cout << ":Вправо" << endl;

	{
		SetColor(Purpur, Black);
		GotoXY(2, 2); //Рисуем верхнюю горизонтальную линию-стенку
		int m = 0;
		for (m = 0; m < 60; m++)
		{
			printf("*");
		}
	}
	{
		GotoXY(2, 24); //Рисуем нижнюю горизонтальную линию-стенку
		int m = 0;
		for (m = 0; m < 60; m++)
		{
			printf("*");
		}
	}
	{	//Рисуем левую вертикальную линию-стенку
		for (int n = 2; n < 25; n++)
		{
			GotoXY(2, n); cout << "*" << endl;
		}
	}
	{   //Рисуем правую вертикальную линию-стенку
		for (int n = 2; n < 25; n++)
		{
			GotoXY(61, n); cout << "*" << endl;
		}
	}
}


//Функция которая двигает и рисует
enum { KONEC, STENA, PLUS, MOVE };
int Move(Game &g)
{
	int & n = g.snake.PCount;
	COORD head = g.snake.t[n - 1]; //голова
	COORD tail = g.snake.t[0]; //хвост
	COORD next;
	next.X = head.X + g.dx;
	next.Y = head.Y + g.dy; //проверка следующей точки по направлению

	if (next.X < 3 || next.Y < 3 || next.X > 60 || next.Y > 23)//проверка столкновение со стеной
		return STENA;

	if (n > 4)
	{
		for (int i = 0; i < n; i++)
			if (next.X == g.snake.t[i].X && next.Y == g.snake.t[i].Y) //проверка, наехали на себя
				return KONEC;
	}

	if (next.X == g.apple.X && next.Y == g.apple.Y)
	{
		COORD*temp = new COORD[++n]; //новый масив
		for (int i = 0; i < n; i++)
			temp[i] = g.snake.t[i];
		temp[n - 1] = next;
		delete[] g.snake.t;
		g.snake.t = temp;

		SetConsoleCursorPosition(hConsole, head);
		SetConsoleTextAttribute(hConsole, 0x0a);
		printf("*");
		SetConsoleCursorPosition(hConsole, next);
		SetConsoleTextAttribute(hConsole, 0x0a);
		printf("%c", 1);
		PlusApple(g);
		return PLUS;
	}

	for (int i = 0; i < n - 1; i++)
		g.snake.t[i] = g.snake.t[i + 1];
	g.snake.t[n - 1] = next;
	SetConsoleCursorPosition(hConsole, tail);
	printf(" ");

	SetConsoleCursorPosition(hConsole, head);
	SetConsoleTextAttribute(hConsole, 0x0a);
	printf("*");
	SetConsoleCursorPosition(hConsole, next);
	SetConsoleTextAttribute(hConsole, 0x0f);
	printf("%c", 1);

	return MOVE;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //получаем дескриптор консоли
	int key = 0, count = 0;
	bool Pause = false;
	Game g;
	StartGame(g);
	_STENA();
	srand(time(0));
	bool pause = false;
	while (key != 27)
	{
		while (!_kbhit())
		{
			if (Pause == true)
			{
				Sleep(1);
				continue;
			}

			switch (Move(g))//движение
			{

			case PLUS:
				++count;
				g.pause -= 1;
				SetColor(Cyan, Black);
				GotoXY(64, 2); cout << "Данные:" << endl;
				GotoXY(64, 3); cout << "Собрано яблок:" << count << endl;
				GotoXY(64, 4); cout << "Длина змейки:" << g.snake.PCount << endl;
				GotoXY(64, 8); cout << "Esc:Выход" << endl;
				GotoXY(64, 9); cout << "P:Пауза" << endl;
				GotoXY(64, 7); cout << "Управление:" << endl;
				GotoXY(64, 13); printf("%c", 24); cout << ":Вверх" << endl;
				GotoXY(64, 14); printf("%c", 25); cout << ":Вниз" << endl;
				GotoXY(64, 15); printf("%c", 27); cout << ":Влево" << endl;
				GotoXY(64, 16); printf("%c", 26); cout << ":Вправо" << endl;
				if (count == 50)
				{
					SetColor(Purpur, Black);
					GotoXY(24, 1); cout << "Вы Выиграли! Поздравляем!" << endl;
					_getch();
					return(0);
				}
				break;

			case STENA:

			case KONEC:
				GotoXY(23, 1); printf("Увы, Вы проиграли!");
				_getch();
				break;
			}

			Sleep(g.pause); //Задержка
		}
		key = _getch();

		if (key == 'P' || key == 'p')
			Pause = !Pause;
		else if (key == 0 || key == 224)
		{
			key = _getch();

			if (key == 72 && g.nap != DOWN)
			{
				g.nap = UP;
				g.dx = 0;
				g.dy = -1;
			}
			else if (key == 80 && g.nap != UP)
			{
				g.nap = DOWN;
				g.dx = 0;
				g.dy = 1;
			}
			else if (key == 75 && g.nap != RIGHT)
			{
				g.nap = LEFT;
				g.dx = -1;
				g.dy = 0;
			}
			else if (key == 77 && g.nap != LEFT)
			{
				g.nap = RIGHT;
				g.dx = 1;
				g.dy = 0;
			}
		}
	}
}
