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
	// Деструктор  
	~CreditStruct() { Npay = 0, sumpay = 0, pay = 0, difprocent = 0, AccountBal = 0;	status = ""; }

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
	int ShowClientSumma() { return  Summa; } //показать сумму на счету
	void setClientCredit(string _ClCr) { ClientCredit = _ClCr; } //запишем сведения по кредиту
	void setClientSumma(int _Sum) { Summa = Summa + _Sum; } //запишем сведения по кредиту
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
	int CalcProcent(int _year, int _summ)  //вычислим процент по кредиту в зависимости от года и суммы
	{
		CreditProcent = yearCredit[1][_year] - summCredit[1][_summ];
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
				CreditClient[i].status = "Не оплачен";
			}
			else
			{
				CreditClient[i].Npay = i;
				CreditClient[i].pay = _summ / SizeCreditStruct;
				CreditClient[i].difprocent = CreditClient[i - 1].AccountBal / 100 * _procent / 12;
				CreditClient[i].sumpay = CreditClient[i].pay + CreditClient[i].difprocent;
				CreditClient[i].AccountBal = CreditClient[i - 1].AccountBal - CreditClient[i].pay;
				CreditClient[i].status = "Не оплачен";
			}
		}
	}
	void ShowCredit()
	{
		cout << "Номер платежа  Сумма плтежа  Базовый платеж  Поцент платежа  Остаток  Состояние" << endl;
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
			if (CreditClient[i].status == "Не оплачен") { return CreditClient[i].sumpay; }
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

			if (CreditClient[i].status == "Не оплачен")
			{
				if (_summ == CreditClient[i].sumpay) { CreditClient[i].status = "Оплачено"; break; }
				else
				{
					if (!trigerpay)
					{
						CreditClient[i].pay = _summ - CreditClient[i].sumpay;
						CreditClient[i].AccountBal = CreditClient[i].AccountBal - CreditClient[i].pay;
						CreditClient[i].status = "Оплачено";
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
						CreditClient[i].status = "Не оплачен";
					}

				}
			}
		}
	}
	int ShowAccountBal()
	{
		for (int i = 0; i < SizeCreditStruct; i++)
		{
			if (CreditClient[i].status == "Не оплачен") { return CreditClient[i].AccountBal; }
		}
	}
};

int main()
{
	static const int LENGTH = 5;
	ProcesCenter Clients[LENGTH] // создадим 5 клиентов банка
	{
		ProcesCenter(1,"Петров  А.А.",100000,"111"),
		ProcesCenter(2,"Иванов  Е.П.",2000,"222"),
		ProcesCenter(3,"Сидоров С.П.",30000,"333"),
		ProcesCenter(4,"Макаров Н.М.",50000,"444"),
		ProcesCenter(5,"Слиж  А.Е."  ,100000,"555")
	};
	Credit ClentCredit[LENGTH]; //создадим нулевой обьект для 1 кредита
								//Credit ClentCredit(Clients[0].ShowLog()); //создадим нулевой обьект для кредита
	int SA = -1;  //номер счета кредита=зарплата для клиента с которым будем работать
	int CSA = -1;
	int year, summ;
	setlocale(LC_ALL, "Russian");
	while (1)
	{
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
			if (SA == -1) cout << "Пользователь не авторизирован, попробуйте снова" << endl;
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
			case 1:  //показать информацию о доступных клиенту кредитах
			{
				ClentCredit[CSA].ShowInfоCredit();
				system("pause");
				system("cls");
				break;
			}
			case 2: // проверить наличие взятого в банка кредита,
			{
				if (Clients[SA].ShowClientCredit() == "") cout << "Нет кредита "; else   cout << "Найдем кредит " << Clients[SA].ShowClientCredit();
				system("pause");
				system("cls");
				break;
			}
			case 3: //проверить возможность получения выбранного кредита, 
			{
				cout << "Выберите на сколько лет вы хотите взять кредит" << endl;
				for (int i = 0; i < 5; i++)
				{
					cout << i << ") " << ClentCredit[CSA].yearCredit[0][i] << "  ";
				}
				cin >> year;
				cout << "Выберите на какую сумму вы хотите взять кредит не более 3000 т.р." << endl;
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
				// Считать, что кредит одобряется банком клиенту, если текущая сумма на его зарплатном счету достаточна для шести ежемесячных выплат
				int sixSum = 0;
				for (int i = 0; i < 6; i++)
				{
					sixSum = sixSum + ClentCredit[CSA].ShowPay(i);
				}
				if (sixSum <= Clients[SA].ShowClientSumma()) { cout << "Вы можете получить кредит" << endl; }
				else { cout << "Этот кредит вам не подходит, попробуйте другой" << endl; }
				ClentCredit[CSA].clearCredit(); // очистим структуру с описанием кредита
				system("pause");
				system("cls");
				break;
			}
			case 4:
			{
				cout << "Выберите на сколько лет вы хотите взять кредит" << endl;
				for (int i = 0; i < 5; i++)
				{
					cout << i << ") " << ClentCredit[CSA].yearCredit[0][i] << "  ";
				}
				cin >> year;
				cout << "Выберите на какую сумму вы хотите взять кредит не более 3000 т.р." << endl;
				cin >> summ;
				int procent = 0;
				int i = 0;
				while (i<4)
				{
					if (summ <= ClentCredit[CSA].summCredit[0][i])
					{
						procent = ClentCredit[CSA].CalcProcent(year, i);
						Clients[SA].setClientCredit("Кредит сроком " + to_string(ClentCredit[CSA].yearCredit[0][year]) + " год на сумму " + to_string(summ) + "т.р под " + to_string(procent) + "% годовых ");
						i = 4;
					}
					i++;
				}
				ClentCredit[CSA].CreatCredit(year, summ, procent);
				Clients[SA].setClientSumma(summ * 1000);  //запишем сумму кредита на счет
				system("cls");
				cout << "Сумма на вашем счету составляет  " << Clients[SA].ShowClientSumma() << " р." << endl;
				cout << "У вас  " << Clients[SA].ShowClientCredit();
				system("pause");
				system("cls");
				break;
			}

			case 5:
			{
				cout << "У вас " << Clients[SA].ShowClientCredit() << endl;
				ClentCredit[CSA].ShowCredit();
				system("pause");
				system("cls");
				break;
			}

			case 6:
			{
				int minpay = ClentCredit[CSA].ShowCurrentPay();
				cout << "Ваш текущий платеж составляет  " << minpay << "р." << endl << "Ведите сумму для оплаты ";
				int mypay = 0;
				cin >> mypay;
				if (mypay < minpay) { cout << "Сумма списания не может быть меньше чем сумма платежа!  " << minpay << "р." << endl; }
				else ClentCredit[CSA].PayCredit(mypay);
				Clients[SA].setClientSumma(-mypay);
				cout << "Сумма на вашем счету составляет  " << Clients[SA].ShowClientSumma() << " р." << endl;
				system("pause");
				system("cls");
				break;
			}
			case 7:
			{
				int minpay = ClentCredit[CSA].ShowAccountBal();
				int mypay = Clients[SA].ShowClientSumma();
				cout << "Сумма оставшегося долга " << minpay << "р." << endl << "Сумма на вашем счету " << mypay << " р." << endl;
				cout << "Желаете закрыть кредит  Y/N" << endl;
				string s;
				cin >> s;
				if (s == "Y" && minpay <= mypay)
				{
					Clients[SA].setClientSumma(-minpay);
					Clients[SA].setClientCredit("");
					ClentCredit[CSA].clearCredit();
					cout << "Поздравляем ваш кредит закрыт!  " << endl;
				}
				else if (minpay <= mypay) { cout << "Сумма на вашем счету недостаточная для погащения кредита" << endl; }

				system("pause");
				system("cls");
				break;
			}
			case 8:
			{
				cout << "Досвидания" << endl; }
			system("pause");
			system("cls");
			login = false;
			choice = 100;
			}
		}

	}
}//main