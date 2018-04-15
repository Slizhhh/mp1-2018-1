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
	int SalaryAccaunt;			// номер счета
	string FIO;					// ФИО клиента
	int Summa;					// сумма на счету
	string ClientCredit;        // переменная с описанием взятого кредита
	string Password;			// пароль клиента
public:
	ProcesCenter(int _SA, string _FIO, int _S, string _P)  //конструктор 
	{
		SalaryAccaunt = _SA;
		FIO = _FIO;
		Summa = _S;
		ClientCredit = "";
		Password = _P;
	}
	int ShowLog() { return SalaryAccaunt; }  //показать логин*/
	string ShowPas() { return Password; }  //показать пароль
	string ShowFIO() { return FIO; }  //показать пароль
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
	const int yearCredit[5][5]{ { 1,2,3,5,15 },{ 20,18,17,15,10 } };         //Массив для расчета процентов в зависимости от года 
	const int summCredit[4][4]{ { 100, 500, 1000, 3000 },{ 1, 2, 3, 5 } };   //Массив для расчета процентов в зав-ти от суммы
	Credit(int _SA)
	{
		CreditAccaunt = _SA;
		CreditSumma = 0;
		CreditProcent = 0;
		SizeCreditStruct = 0;
		CreditClient = nullptr;
	}
	int CalcProcent(int _year, int _summ)  //вычислим процент по кредиту в зависимости от года и суммы
	{
		return yearCredit[1][_year] - summCredit[1][_summ];
	}
	void ShowInfоCredit() {  //Показать клиенту все возможные варианты кредита
		cout << "Банк предоставляет следующие кредиты:" << endl;
		//Пройдем по всем годам и суммам для вывода процентов
		for (int i = 0; i < 5; i++)
		{
			for (int s = 0; s < 4; s++)
			{
				if (s == 0)  cout << "Кредит сроком " << yearCredit[0][i] << " год на сумму < " << summCredit[0][s] << "т.р.  под " << CalcProcent(i, s) << "% годовых" << endl;
				else   cout << "Кредит сроком " << yearCredit[0][i] << " год на сумму > " << summCredit[0][s - 1] << "т.р  и  < " << summCredit[0][s] << "т.р.  под " << CalcProcent(i, s) << "% годовых" << endl;
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
		cout << "Номер платежа   Сумма плтежа   Базовый платеж    Поцент платежа   Остаток " << endl;
		for (int i = 0; i < SizeCreditStruct; i++)
		{
			cout << CreditClient[i].Npay + 1 << "   " << CreditClient[i].sumpay << "   " << CreditClient[i].pay << "   " << CreditClient[i].difprocent << "   " << CreditClient[i].AccountBal << endl;
		}
	}


};

int main()
{
	static const int LENGTH = 5;
	ProcesCenter Clients[LENGTH] // создадим 5 клиентов банка
	{
		ProcesCenter(1,"Петров  А.А.",10000,"111"),
		ProcesCenter(2,"Иванов  Е.П.",2000,"222"),
		ProcesCenter(3,"Сидоров С.П.",30000,"333"),
		ProcesCenter(4,"Макаров Н.М.",50000,"444"),
		ProcesCenter(5,"Слиж  А.Е."  ,100000,"555")
	};

	int SA = 0;                 //номер счета кредита=зарплата для клиента с которым будем работать
	int year, summ;
	setlocale(LC_ALL, "Russian");
	bool login = false;
	while (!login)
	{
		cout << "Добро пожаловать в банк Рога и Копыта" << endl;
		cout << "Ведите свой номер счета" << endl;
		int log;
		cin >> log;
		cout << "Ведите свой пароль" << endl;
		string pas;
		cin >> pas;
		system("cls");
		for (int i = 0; i<LENGTH; i++)
		{
			if (pas == Clients[i].ShowPas() && log == Clients[i].ShowLog())
			{
				cout << "Добро пожаловать в банк: клиент " << Clients[i].ShowFIO() << endl;
				SA = i;
				login = true;
			}
		}
		if (SA == 0) cout << "Пользователь не авторизирован, попробуйте снова" << endl;
		system("pause");
		system("cls");
	}

	int choice = 0;
	Credit ClentCredit(Clients[SA].ShowLog()); //создадим нулевой обьект для кредита
	while (choice != 100)//При удачной авторизации заходимв другое меню

	{
		cout << "Клиент " << Clients[SA].ShowFIO() << endl;
		cout << "1)Показать информацию о доступных клиенту кредитах " << endl;
		cout << "2)Проверить наличие взятого в банке кредита " << endl;
		cout << "3)Проверить возможность получения выбранного кредита " << endl;
		cout << "4)Получить выбранный кредит " << endl;
		cout << "5)Показать текущее состояние кредита " << endl;
		cout << "6)Погасить начисления по кредиту " << endl;
		cout << "7)Досрочно погасить кредит " << endl;
		cout << "8)Выход " << endl;
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
		{
			ClentCredit.ShowInfоCredit();
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			if (Clients[SA].ShowClientCredit() == "") cout << "Нет кредита "; else   cout << "Найдем кредит " << Clients[SA].ShowClientCredit();
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			cout << "Выберите на сколько лет вы хотите взять кредит" << endl;
			for (int i = 0; i < 5; i++)
			{
				cout << i << ") " << ClentCredit.yearCredit[0][i] << "  ";
			}
			cin >> year;
			cout << "Выберите на какую сумму вы хотите взять кредит не более 3000 т.р." << endl;
			cin >> summ;
			int procent = 0;
			int i = 0;
			while (i<4)
			{
				if (summ <= ClentCredit.summCredit[0][i])
				{
					procent = ClentCredit.CalcProcent(year, i);
					Clients[SA].setClientCredit("Кредит сроком " + to_string(year) + " год на сумму " + to_string(summ) + "т.р под " + to_string(procent) + "% годовых ");
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