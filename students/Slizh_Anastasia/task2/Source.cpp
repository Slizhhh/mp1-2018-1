#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "conio.h"
#include <stdio.h>
#include <time.h>

using namespace std;

class Matrix {
private:
	int **Mat;
	int col, row;
	int sum = 0;
	bool res = false;

	void Create()
	{
		Mat = new int*[col];
		for (int i = 0; i < col; i++)
		{
			Mat[i] = new int[row];
		}
	}

public:
	//�����������
	Matrix(int i, int j) : col(i), row(j) { Create(); }

	//������ 
	//������ � �������� �������
	int& Element(int i, int j)
	{
		if (i < col && j < row) return Mat[i][j];
		else cout << "������";
	}
	//�������� �������
	void ShowMatrix()
	{
		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < row; j++)
			{
				cout.width(4);
				cout << Mat[i][j];
			}
			cout << endl;
		}

	}
	//��������� �� ������������ ������������
	void DiagonalPredomin()
	{
		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < row; j++)
			{
				sum += Mat[i][j];
			}
			sum -= Mat[i][i];
			if (Mat[i][i] <= sum)
				res = false;
			else  res = true;
		}
		if (res == false)
			cout << "������� �� �������� ������������ ������������� " << endl;
		else
			cout << "������� �������� ������������ ������������� " << endl;
	}

	~Matrix();
};

int main()
{
	setlocale(LC_ALL, "RUS");
	int  n, c, r;
	cout << "������� ������ �������\n";
	//cin >> m;
	cin >> n;
	cout << "������� �������� " << n << " �� " << n << endl;
	Matrix Mat(n, n);
	Matrix Mat1(n, n);
	Matrix matSumm(n, n);
	system("pause");
	for (c = 0; c < n; c++)
	{
		for (r = 0; r < n; r++)
		{
			cout << "������� ������� " << c << "," << r << endl;
			cin >> Mat.Element(c, r);
		}
	}
	Mat.ShowMatrix();
	system("pause");
	system("cls");
	Mat.DiagonalPredomin();
	system("pause");
	system("cls");
	cout << "������� ������� � ������� ������� �������� " << endl;
	for (c = 0; c < n; c++)
	{
		for (r = 0; r < n; r++)
		{
			cout << "������� ������� " << c << "," << r << endl;
			cin >> Mat1.Element(c, r);
		}
	}
	Mat1.ShowMatrix();
	system("pause");
	for (c = 0; c < n; c++)
	{
		for (r = 0; r < n; r++)
		{
			matSumm.Element(c, r) = Mat1.Element(c, r) + Mat.Element(c, r);
		}
	}
	matSumm.ShowMatrix();
	system("pause");
}

Matrix::~Matrix()
{
	delete Mat;
}