#pragma once
#include <string>
#include <iostream>

class BankAccount
{
	std::string surname;
	unsigned int number;
	unsigned balance;

public:
	BankAccount();		// Konstruktor, pobiera info potrzebne do za�o�enia konta
	void ShowBalance();	// Pokzauje aktualny stan konta
	void withdraw();	// Wyp�aca / usuwa  pieni�dze z konta
	void deposit();		// Wp�aca / dodaje pieni�dze na konto
	void transfer();	// Przelewa pieni�dze z jednego na drugie konto
};