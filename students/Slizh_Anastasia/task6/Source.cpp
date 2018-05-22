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

//����
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


class  Snake// ��������� ������ 
{
public:COORD * t;
public:int PCount;
};
enum uprawlenie { LEFT, UP, RIGHT, DOWN }; //����������� ������
class Game //�����-��������: ������, �����, ������������ �� X � Y, ��������, �����������
{
public:Snake snake; //������
public:COORD apple; //������
public:int dx, dy; //������������
public:int pause; //��������
public:int nap; //�����������

};


void PlusApple(Game &g) //������� ��������� �����
{
	int i, x, y;
	int n = g.snake.PCount;
	do
	{
		x = rand() % 56 + 3;
		y = rand() % 19 + 3;
		for (i = 0; i < n; i++)
		{
			if (x == g.snake.t[i].X && y == g.snake.t[i].Y) // �������� ���� ������ �� ������� �� ����
				break;
		}
	} while (i < n);
	g.apple.X = x;
	g.apple.Y = y;
	SetConsoleCursorPosition(hConsole, g.apple);
	SetConsoleTextAttribute(hConsole, 0x0c); //���� ������  
	printf("%c", 4);

}


void StartGame(Game &g) // ������ ������ ������ �� ��������� � ��������
{
	system("cls");
	g.snake.PCount = 3; //��������� ����� ������
	g.snake.t = new COORD[3];
	for (int i = 0; i < 3; i++)
	{
		g.snake.t[i].X = 20 + i;
		g.snake.t[i].Y = 20;

	}
	g.dx = 1;
	g.dy = 0;
	g.pause = 100;//�������� ������������ ����
	PlusApple(g);//������ ������
}

void _STENA()
{
	SetColor(Cyan, Black);
	GotoXY(64, 2); cout << "������:" << endl;
	GotoXY(64, 3); cout << "������� �����:0" << endl;
	GotoXY(64, 4); cout << "����� ������:3" << endl;
	GotoXY(64, 8); cout << "Esc:�����" << endl;
	GotoXY(64, 9); cout << "P:�����" << endl;
	GotoXY(64, 7); cout << "����������:" << endl;
	GotoXY(64, 13); printf("%c", 24); cout << ":�����" << endl;
	GotoXY(64, 14); printf("%c", 25); cout << ":����" << endl;
	GotoXY(64, 15); printf("%c", 27); cout << ":�����" << endl;
	GotoXY(64, 16); printf("%c", 26); cout << ":������" << endl;

	{
		SetColor(Purpur, Black);
		GotoXY(2, 2); //������ ������� �������������� �����-������
		int m = 0;
		for (m = 0; m < 60; m++)
		{
			printf("*");
		}
	}
	{
		GotoXY(2, 24); //������ ������ �������������� �����-������
		int m = 0;
		for (m = 0; m < 60; m++)
		{
			printf("*");
		}
	}
	{	//������ ����� ������������ �����-������
		for (int n = 2; n < 25; n++)
		{
			GotoXY(2, n); cout << "*" << endl;
		}
	}
	{   //������ ������ ������������ �����-������
		for (int n = 2; n < 25; n++)
		{
			GotoXY(61, n); cout << "*" << endl;
		}
	}
}


//������� ������� ������� � ������
enum { KONEC, STENA, PLUS, MOVE };
int Move(Game &g)
{
	int & n = g.snake.PCount;
	COORD head = g.snake.t[n - 1]; //������
	COORD tail = g.snake.t[0]; //�����
	COORD next;
	next.X = head.X + g.dx;
	next.Y = head.Y + g.dy; //�������� ��������� ����� �� �����������

	if (next.X < 3 || next.Y < 3 || next.X > 60 || next.Y > 23)//�������� ������������ �� ������
		return STENA;

	if (n > 4)
	{
		for (int i = 0; i < n; i++)
			if (next.X == g.snake.t[i].X && next.Y == g.snake.t[i].Y) //��������, ������� �� ����
				return KONEC;
	}

	if (next.X == g.apple.X && next.Y == g.apple.Y)
	{
		COORD*temp = new COORD[++n]; //����� �����
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
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //�������� ���������� �������
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

			switch (Move(g))//��������
			{

			case PLUS:
				++count;
				g.pause -= 1;
				SetColor(Cyan, Black);
				GotoXY(64, 2); cout << "������:" << endl;
				GotoXY(64, 3); cout << "������� �����:" << count << endl;
				GotoXY(64, 4); cout << "����� ������:" << g.snake.PCount << endl;
				GotoXY(64, 8); cout << "Esc:�����" << endl;
				GotoXY(64, 9); cout << "P:�����" << endl;
				GotoXY(64, 7); cout << "����������:" << endl;
				GotoXY(64, 13); printf("%c", 24); cout << ":�����" << endl;
				GotoXY(64, 14); printf("%c", 25); cout << ":����" << endl;
				GotoXY(64, 15); printf("%c", 27); cout << ":�����" << endl;
				GotoXY(64, 16); printf("%c", 26); cout << ":������" << endl;
				if (count == 50)
				{
					SetColor(Purpur, Black);
					GotoXY(24, 1); cout << "�� ��������! �����������!" << endl;
					_getch();
					return(0);
				}
				break;

			case STENA:

			case KONEC:
				GotoXY(23, 1); printf("���, �� ���������!");
				_getch();
				break;
			}

			Sleep(g.pause); //��������
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
