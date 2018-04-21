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
	string status;
	CreditStruct() { Npay = 0, sumpay = 0, pay = 0, difprocent = 0, AccountBal = 0; status = ""; }
	// ����������  
	~CreditStruct() { Npay = 0, sumpay = 0, pay = 0, difprocent = 0, AccountBal = 0;	status = ""; }

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
	int ShowClientSumma() { return  Summa; } //�������� ����� �� �����
	void setClientCredit(string _ClCr) { ClientCredit = _ClCr; } //������� �������� �� �������
	void setClientSumma(int _Sum) { Summa = Summa + _Sum; } //������� �������� �� �������
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
	Credit()
	{
		CreditAccaunt = 0;
		CreditSumma = 0;
		CreditProcent = 0;
		SizeCreditStruct = 0;
		CreditClient = nullptr;
	}



	int ShowCreditAccaunt() { return CreditAccaunt; }
	void setCreditAccaunt(int _i) { CreditAccaunt = _i; }
	int CalcProcent(int _year, int _summ)  //�������� ������� �� ������� � ����������� �� ���� � �����
	{
		CreditProcent = yearCredit[1][_year] - summCredit[1][_summ];
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
				CreditClient[i].status = "�� �������";
			}
			else
			{
				CreditClient[i].Npay = i;
				CreditClient[i].pay = _summ / SizeCreditStruct;
				CreditClient[i].difprocent = CreditClient[i - 1].AccountBal / 100 * _procent / 12;
				CreditClient[i].sumpay = CreditClient[i].pay + CreditClient[i].difprocent;
				CreditClient[i].AccountBal = CreditClient[i - 1].AccountBal - CreditClient[i].pay;
				CreditClient[i].status = "�� �������";
			}
		}
	}
	void ShowCredit()
	{
		cout << "����� �������  ����� ������  ������� ������  ������ �������  �������  ���������" << endl;
		for (int i = 0; i < SizeCreditStruct; i++)
		{
			cout << "     " << CreditClient[i].Npay + 1 << "          " << CreditClient[i].sumpay << "         " << CreditClient[i].pay << "           " << CreditClient[i].difprocent << "        " << CreditClient[i].AccountBal << "        " << CreditClient[i].status << endl;
		}
	}
	int ShowPay(int _i) { return CreditClient[_i].sumpay; }
	void clearCredit() { CreditClient = nullptr; }
	int ShowCurrentPay()
	{
		for (int i = 0; i < SizeCreditStruct; i++)
		{
			if (CreditClient[i].status == "�� �������") { return CreditClient[i].sumpay; }
		}
	}

	void PayCredit(int _summ)
	{
		bool trigerpay = false, zero = false;
		for (int i = 0; i < SizeCreditStruct; i++)
		{
			if (zero)
			{
				CreditClient[i].Npay = 0;
				CreditClient[i].pay = 0;
				CreditClient[i].difprocent = 0;
				CreditClient[i].sumpay = 0;
				CreditClient[i].AccountBal = 0;
				CreditClient[i].status = "";
			}

			if (CreditClient[i].status == "�� �������")
			{
				if (_summ == CreditClient[i].sumpay) { CreditClient[i].status = "��������"; break; }
				else
				{
					if (!trigerpay)
					{
						CreditClient[i].pay = _summ - CreditClient[i].sumpay;
						CreditClient[i].AccountBal = CreditClient[i].AccountBal - CreditClient[i].pay;
						CreditClient[i].status = "��������";
						trigerpay = true;
					}
					else
					{
						CreditClient[i].difprocent = CreditClient[i - 1].AccountBal / 100 * CreditProcent / 12;
						CreditClient[i].sumpay = CreditClient[i].pay + CreditClient[i].difprocent;
						if (CreditClient[i - 1].AccountBal - CreditClient[i].pay < 0)
						{
							CreditClient[i].AccountBal = 0;
							CreditClient[i].pay = CreditClient[i].pay - abs(CreditClient[i - 1].AccountBal - CreditClient[i].pay);
							zero = true;
						}
						else CreditClient[i].AccountBal = CreditClient[i - 1].AccountBal - CreditClient[i].pay;
						CreditClient[i].status = "�� �������";
					}

				}
			}
		}
	}
	int ShowAccountBal()
	{
		for (int i = 0; i < SizeCreditStruct; i++)
		{
			if (CreditClient[i].status == "�� �������") { return CreditClient[i].AccountBal; }
		}
	}
};

int main()
{
	static const int LENGTH = 5;
	ProcesCenter Clients[LENGTH] // �������� 5 �������� �����
	{
		ProcesCenter(1,"������  �.�.",100000,"111"),
		ProcesCenter(2,"������  �.�.",2000,"222"),
		ProcesCenter(3,"������� �.�.",30000,"333"),
		ProcesCenter(4,"������� �.�.",50000,"444"),
		ProcesCenter(5,"����  �.�."  ,100000,"555")
	};
	Credit ClentCredit[LENGTH]; //�������� ������� ������ ��� 1 �������
								//Credit ClentCredit(Clients[0].ShowLog()); //�������� ������� ������ ��� �������
	int SA = -1;  //����� ����� �������=�������� ��� ������� � ������� ����� ��������
	int CSA = -1;
	int year, summ;
	setlocale(LC_ALL, "Russian");
	while (1)
	{
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
			if (SA == -1) cout << "������������ �� �������������, ���������� �����" << endl;
			system("pause");
			system("cls");
		}
		int choice = 0; int pos = 0;
		while (choice < LENGTH)
		{
			if (ClentCredit[choice].ShowCreditAccaunt() == 0) { pos = choice; }
			if (SA == ClentCredit[choice].ShowCreditAccaunt()) { CSA = choice;  break; }
			choice++;
		}
		if (CSA = -1) { ClentCredit[pos].setCreditAccaunt(SA); CSA = pos; }

		choice = 0;
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
			case 1:  //�������� ���������� � ��������� ������� ��������
			{
				ClentCredit[CSA].ShowInf�Credit();
				system("pause");
				system("cls");
				break;
			}
			case 2: // ��������� ������� ������� � ����� �������,
			{
				if (Clients[SA].ShowClientCredit() == "") cout << "��� ������� "; else   cout << "������ ������ " << Clients[SA].ShowClientCredit();
				system("pause");
				system("cls");
				break;
			}
			case 3: //��������� ����������� ��������� ���������� �������, 
			{
				cout << "�������� �� ������� ��� �� ������ ����� ������" << endl;
				for (int i = 0; i < 5; i++)
				{
					cout << i << ") " << ClentCredit[CSA].yearCredit[0][i] << "  ";
				}
				cin >> year;
				cout << "�������� �� ����� ����� �� ������ ����� ������ �� ����� 3000 �.�." << endl;
				cin >> summ;
				int procent = 0;
				int i = 0;
				while (i < 4)
				{
					if (summ <= ClentCredit[CSA].summCredit[0][i])
					{
						procent = ClentCredit[CSA].CalcProcent(year, i);
						i = 4;
					}
					i++;
				}
				ClentCredit[CSA].CreatCredit(year, summ, procent);
				// �������, ��� ������ ���������� ������ �������, ���� ������� ����� �� ��� ���������� ����� ���������� ��� ����� ����������� ������
				int sixSum = 0;
				for (int i = 0; i < 6; i++)
				{
					sixSum = sixSum + ClentCredit[CSA].ShowPay(i);
				}
				if (sixSum <= Clients[SA].ShowClientSumma()) { cout << "�� ������ �������� ������" << endl; }
				else { cout << "���� ������ ��� �� ��������, ���������� ������" << endl; }
				ClentCredit[CSA].clearCredit(); // ������� ��������� � ��������� �������
				system("pause");
				system("cls");
				break;
			}
			case 4:
			{
				cout << "�������� �� ������� ��� �� ������ ����� ������" << endl;
				for (int i = 0; i < 5; i++)
				{
					cout << i << ") " << ClentCredit[CSA].yearCredit[0][i] << "  ";
				}
				cin >> year;
				cout << "�������� �� ����� ����� �� ������ ����� ������ �� ����� 3000 �.�." << endl;
				cin >> summ;
				int procent = 0;
				int i = 0;
				while (i<4)
				{
					if (summ <= ClentCredit[CSA].summCredit[0][i])
					{
						procent = ClentCredit[CSA].CalcProcent(year, i);
						Clients[SA].setClientCredit("������ ������ " + to_string(ClentCredit[CSA].yearCredit[0][year]) + " ��� �� ����� " + to_string(summ) + "�.� ��� " + to_string(procent) + "% ������� ");
						i = 4;
					}
					i++;
				}
				ClentCredit[CSA].CreatCredit(year, summ, procent);
				Clients[SA].setClientSumma(summ * 1000);  //������� ����� ������� �� ����
				system("cls");
				cout << "����� �� ����� ����� ����������  " << Clients[SA].ShowClientSumma() << " �." << endl;
				cout << "� ���  " << Clients[SA].ShowClientCredit();
				system("pause");
				system("cls");
				break;
			}

			case 5:
			{
				cout << "� ��� " << Clients[SA].ShowClientCredit() << endl;
				ClentCredit[CSA].ShowCredit();
				system("pause");
				system("cls");
				break;
			}

			case 6:
			{
				int minpay = ClentCredit[CSA].ShowCurrentPay();
				cout << "��� ������� ������ ����������  " << minpay << "�." << endl << "������ ����� ��� ������ ";
				int mypay = 0;
				cin >> mypay;
				if (mypay < minpay) { cout << "����� �������� �� ����� ���� ������ ��� ����� �������!  " << minpay << "�." << endl; }
				else ClentCredit[CSA].PayCredit(mypay);
				Clients[SA].setClientSumma(-mypay);
				cout << "����� �� ����� ����� ����������  " << Clients[SA].ShowClientSumma() << " �." << endl;
				system("pause");
				system("cls");
				break;
			}
			case 7:
			{
				int minpay = ClentCredit[CSA].ShowAccountBal();
				int mypay = Clients[SA].ShowClientSumma();
				cout << "����� ����������� ����� " << minpay << "�." << endl << "����� �� ����� ����� " << mypay << " �." << endl;
				cout << "������� ������� ������  Y/N" << endl;
				string s;
				cin >> s;
				if (s == "Y" && minpay <= mypay)
				{
					Clients[SA].setClientSumma(-minpay);
					Clients[SA].setClientCredit("");
					ClentCredit[CSA].clearCredit();
					cout << "����������� ��� ������ ������!  " << endl;
				}
				else if (minpay <= mypay) { cout << "����� �� ����� ����� ������������� ��� ��������� �������" << endl; }

				system("pause");
				system("cls");
				break;
			}
			case 8:
			{
				cout << "����������" << endl; }
			system("pause");
			system("cls");
			login = false;
			choice = 100;
			}
		}

	}
}//main