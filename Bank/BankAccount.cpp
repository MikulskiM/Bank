#include <iostream>
#include <string>
#include "BankAccount.h"

BankAccount::BankAccount()
{
	std::cout << "\nTWORZENIE KONTA\nNazwisko: ";
	std::cin >> surname;
	std::cout << "numer konta: ";
	std::cin >> number;
	balance = 0;
};
void BankAccount::ShowBalance()		// Pokzauje aktualny stan konta
{
	std::cout << "\nTwoj stan konta to: "<<balance<<"\n";
};
void BankAccount::withdraw()	// Wyp�aca / usuwa  pieni�dze z konta
{
	int withdraw;
	std::cout << "\nIle PLN chcesz wyplacic? ";
	std::cin >> withdraw;
	balance = balance - withdraw;
	std::cout << "Twoj stan konta po wyplaceniu pieniedzy: "<<balance<<"\n";
};
void BankAccount::deposit()		// Wp�aca / dodaje pieni�dze na konto
{
	int deposit;
	std::cout << "\nIle PLN chcesz wplacic? ";
	std::cin >> deposit;
	balance = balance + deposit;
	std::cout << "Twoj stan konta po wplaceniu pieniedzy: " << balance << "\n";
};
void BankAccount::transfer()	//przelewa pieni�dze z jednego na drugie konto
{

};
