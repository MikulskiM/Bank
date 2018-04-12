#include <iostream>
#include <string>
#include <vector>
#include "BankAccount.h"

//using namespace std;

int main()
{
	//std::vector <BankAccount> bank;

	//bank.push_back();

	BankAccount konto1;
	//BankAccount konto2;
	//BankAccount konto3;
	konto1.ShowBalance();
	konto1.deposit();
	konto1.withdraw();






	system("pause");
	return 0;
}