#pragma once
#include <string>
#include <iostream>

class BankAccount
{
	std::string surname;
	unsigned int number;
	unsigned balance;

public:
	BankAccount();		// Konstruktor, pobiera info potrzebne do za³o¿enia konta
	void ShowBalance();	// Pokzauje aktualny stan konta
	void withdraw();	// Wyp³aca / usuwa  pieni¹dze z konta
	void deposit();		// Wp³aca / dodaje pieni¹dze na konto
	void transfer();	// Przelewa pieni¹dze z jednego na drugie konto
};