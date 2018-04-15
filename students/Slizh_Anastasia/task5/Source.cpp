#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>

using namespace std;

struct CreditStruct {
	int Npay, sumpay, pay, difprocent, AccountBal;
	CreditStruct() { Npay = 0, sumpay = 0, pay = 0, difprocent = 0, AccountBal = 0; }

};

class ProcesCenter
{
private:
	int SalaryAccaunt;			// ����� �����
	string FIO;					// ��� �������
	int Summa;					// ����� �� �����
	string ClientCredit;        // ���������� � ��������� ������� �������
	string Password;			// ������ �������
public:
	ProcesCenter(int _SA, string _FIO, int _S, string _P)  //����������� 
	{
		SalaryAccaunt = _SA;
		FIO = _FIO;
		Summa = _S;
		ClientCredit = "";
		Password = _P;
	}
	int ShowLog() { return SalaryAccaunt; }  //�������� �����*/
	string ShowPas() { return Password; }  //�������� ������
	string ShowFIO() { return FIO; }  //�������� ������
	string ShowClientCredit() { return  ClientCredit; }
	void setClientCredit(string _ClCr)
	{
		ClientCredit = _ClCr;
	}
};


class Credit
{
private:
	int CreditAccaunt;
	int CreditSumma;
	int CreditProcent;
	int SizeCreditStruct;
	CreditStruct *CreditClient;
public:
	int Size;
	const int yearCredit[5][5]{ { 1,2,3,5,15 },{ 20,18,17,15,10 } };         //������ ��� ������� ��������� � ����������� �� ���� 
	const int summCredit[4][4]{ { 100, 500, 1000, 3000 },{ 1, 2, 3, 5 } };   //������ ��� ������� ��������� � ���-�� �� �����
	Credit(int _SA)
	{
		CreditAccaunt = _SA;
		CreditSumma = 0;
		CreditProcent = 0;
		SizeCreditStruct = 0;
		CreditClient = nullptr;
	}
	int CalcProcent(int _year, int _summ)  //�������� ������� �� ������� � ����������� �� ���� � �����
	{
		return yearCredit[1][_year] - summCredit[1][_summ];
	}
	void ShowInf�Credit() {  //�������� ������� ��� ��������� �������� �������
		cout << "���� ������������� ��������� �������:" << endl;
		//������� �� ���� ����� � ������ ��� ������ ���������
		for (int i = 0; i < 5; i++)
		{
			for (int s = 0; s < 4; s++)
			{
				if (s == 0)  cout << "������ ������ " << yearCredit[0][i] << " ��� �� ����� < " << summCredit[0][s] << "�.�.  ��� " << CalcProcent(i, s) << "% �������" << endl;
				else   cout << "������ ������ " << yearCredit[0][i] << " ��� �� ����� > " << summCredit[0][s - 1] << "�.�  �  < " << summCredit[0][s] << "�.�.  ��� " << CalcProcent(i, s) << "% �������" << endl;
			}
		}
	}
	void CreatCredit(int _year, int _summ, int _procent)
	{
		SizeCreditStruct = yearCredit[0][_year] * 12;
		_summ = _summ * 1000;
		CreditClient = new CreditStruct[SizeCreditStruct];
		for (int i = 0; i < SizeCreditStruct; i++)
		{
			if (i == 0)
			{
				CreditClient[i].Npay = i;
				CreditClient[i].pay = _summ / SizeCreditStruct;
				CreditClient[i].difprocent = _summ / 100 * _procent / 12;
				CreditClient[i].sumpay = CreditClient[i].pay + CreditClient[i].difprocent;
				CreditClient[i].AccountBal = _summ - CreditClient[i].pay;
			}
			else
			{
				CreditClient[i].Npay = i;
				CreditClient[i].pay = _summ / SizeCreditStruct;
				CreditClient[i].difprocent = CreditClient[i - 1].AccountBal / 100 * _procent / 12;
				CreditClient[i].sumpay = CreditClient[i].pay + CreditClient[i].difprocent;
				CreditClient[i].AccountBal = CreditClient[i - 1].AccountBal - CreditClient[i].pay;
			}

		}

	}
	void ShowCredit()
	{
		cout << "����� �������   ����� ������   ������� ������    ������ �������   ������� " << endl;
		for (int i = 0; i < SizeCreditStruct; i++)
		{
			cout << CreditClient[i].Npay + 1 << "   " << CreditClient[i].sumpay << "   " << CreditClient[i].pay << "   " << CreditClient[i].difprocent << "   " << CreditClient[i].AccountBal << endl;
		}
	}


};

int main()
{
	static const int LENGTH = 5;
	ProcesCenter Clients[LENGTH] // �������� 5 �������� �����
	{
		ProcesCenter(1,"������  �.�.",10000,"111"),
		ProcesCenter(2,"������  �.�.",2000,"222"),
		ProcesCenter(3,"������� �.�.",30000,"333"),
		ProcesCenter(4,"������� �.�.",50000,"444"),
		ProcesCenter(5,"����  �.�."  ,100000,"555")
	};

	int SA = 0;                 //����� ����� �������=�������� ��� ������� � ������� ����� ��������
	int year, summ;
	setlocale(LC_ALL, "Russian");
	bool login = false;
	while (!login)
	{
		cout << "����� ���������� � ���� ���� � ������" << endl;
		cout << "������ ���� ����� �����" << endl;
		int log;
		cin >> log;
		cout << "������ ���� ������" << endl;
		string pas;
		cin >> pas;
		system("cls");
		for (int i = 0; i<LENGTH; i++)
		{
			if (pas == Clients[i].ShowPas() && log == Clients[i].ShowLog())
			{
				cout << "����� ���������� � ����: ������ " << Clients[i].ShowFIO() << endl;
				SA = i;
				login = true;
			}
		}
		if (SA == 0) cout << "������������ �� �������������, ���������� �����" << endl;
		system("pause");
		system("cls");
	}

	int choice = 0;
	Credit ClentCredit(Clients[SA].ShowLog()); //�������� ������� ������ ��� �������
	while (choice != 100)//��� ������� ����������� �������� ������ ����

	{
		cout << "������ " << Clients[SA].ShowFIO() << endl;
		cout << "1)�������� ���������� � ��������� ������� �������� " << endl;
		cout << "2)��������� ������� ������� � ����� ������� " << endl;
		cout << "3)��������� ����������� ��������� ���������� ������� " << endl;
		cout << "4)�������� ��������� ������ " << endl;
		cout << "5)�������� ������� ��������� ������� " << endl;
		cout << "6)�������� ���������� �� ������� " << endl;
		cout << "7)�������� �������� ������ " << endl;
		cout << "8)����� " << endl;
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
		{
			ClentCredit.ShowInf�Credit();
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			if (Clients[SA].ShowClientCredit() == "") cout << "��� ������� "; else   cout << "������ ������ " << Clients[SA].ShowClientCredit();
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			cout << "�������� �� ������� ��� �� ������ ����� ������" << endl;
			for (int i = 0; i < 5; i++)
			{
				cout << i << ") " << ClentCredit.yearCredit[0][i] << "  ";
			}
			cin >> year;
			cout << "�������� �� ����� ����� �� ������ ����� ������ �� ����� 3000 �.�." << endl;
			cin >> summ;
			int procent = 0;
			int i = 0;
			while (i<4)
			{
				if (summ <= ClentCredit.summCredit[0][i])
				{
					procent = ClentCredit.CalcProcent(year, i);
					Clients[SA].setClientCredit("������ ������ " + to_string(year) + " ��� �� ����� " + to_string(summ) + "�.� ��� " + to_string(procent) + "% ������� ");
					i = 4;
				}
				i++;
			}
			ClentCredit.CreatCredit(year, summ, procent);
			ClentCredit.ShowCredit();
		}
		default:
			break;
		}

	}

}//main