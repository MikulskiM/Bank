#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>

class BankAccount		// ---------------------------------------------- klasa BankAccount ---------------------------------------------------
{
public:
	std::string firstName;	// imie wlascicela konta
	std::string lastName;	// nazwisko wlasciciela konta
	int accountNumber;		// numer konta ( 4 cyfrowy )
	int balance;			// stan konta $$$

	BankAccount* next;		// wskaznik na nastepne konto w banku
	BankAccount* previous;


	BankAccount();
							//BankAccount(std::string first_name, std::string last_name, int account_number, int balance);
	void withdraw();	// Wyp³aca / usuwa  pieniadze z konta
	void withdraw(int money);	// Wyp³aca / usuwa  pieniadze z konta
	void deposit();		// wp³aca pieniadze na konto (dodaje pieniadze)
	void deposit(int money);		// wp³aca pieniadze na konto (dodaje pieniadze)
	void showAccount();	// wyswietla aktualny stan konta
};

BankAccount::BankAccount() {
	
	balance = 0;
	next = 0;
	previous = 0;
}

void BankAccount::withdraw() {
	std::cout << "\nHow much do you want to withdraw? ";
	int cash;
	do {
		std::cin >> cash;
		if (cash < 0)
			std::cout << "\n\t You can't withdraw less than 0$\n";
		else if (cash > balance)
			std::cout << "\n\t You can't withdraw more than you have ("<<balance<<"$)\nTry again: ";
	} while (cash<0 || cash>balance);
	
	balance -= cash;
}

void BankAccount::withdraw(int money) {
	balance -= money;
}

void BankAccount::deposit() {
	std::cout << "\nHow much do you want to deposit? ";
	int cash;
	do {
		std::cin >> cash;
		if (cash < 0)
			std::cout << "\n\t You can't deposit less than 0$\n Try again: ";
	} while (cash<0);

	balance += cash;
}

void BankAccount::deposit(int money) {
	balance += money;
}

void BankAccount::showAccount() {
	std::cout << "\n\tFirst name: " << firstName ;
	std::cout << "\n\tLast name: " << lastName;
	std::cout << "\n\taccount number: " << accountNumber;
	std::cout << "\n\taccount balance: " << balance << "$\n";
}

class Bank		// ---------------------------------------------------- klasa Bank --------------------------------------------------------------------------
{
public:

	BankAccount* first;				// wskaznik na pierwsze konto w liscie ktora jest bank ( dzia³a na zasadzie listy dwukierunkowej )
	BankAccount* last;

	Bank();
	void newAccount();				// zaklada nowe konto
	void newAccount(std::string first_name, std::string last_name, int account_number, int _balance);	// zaklada konto dla podanych danych ( uzywam tylko przy load())
	void deleteAccount();			// usuwa wskazane konto
	void transfer();				// przelej pieniadze z jednego konta na drugie
	void displayAllAccounts();		// wyswietl wszystkie konta
	int howManyAccounts();			// zwraca iloœæ kont w banku
	void save();					// zapisuje Bank w pliku tekstowym bank_data.txt
	void load();					// wczytuje dane banku z pliku tekstowym bank_data.txt
	void overviewMode();
};

Bank::Bank() {
	first = 0;
	last = 0;
}

void Bank::newAccount() {
	BankAccount* nowy = new BankAccount;

	std::cout << "\n\tCreating new account:\nfirst name: ";
	std::cin >> nowy->firstName;
	std::cout << "last name: ";
	std::cin >> nowy->lastName;
	do {
		std::cout << "account number: ";
		std::cin >> nowy->accountNumber;
		if (nowy->accountNumber < 1000 || nowy->accountNumber > 9999)
			std::cout << "\n\taccount number must contain 4 digits. Try againt\n";
	} while (nowy->accountNumber <1000 || nowy->accountNumber > 9999);
	

	if (first == 0) {
		first = nowy;
		last = nowy;
	}
	else {
		first->next = nowy;
		nowy->previous = first;
		nowy->next = 0;
		first = nowy;
	}
}

void Bank::newAccount(std::string firstName, std::string lastName, int accountNumber, int balance) {
	BankAccount* nowy = new BankAccount;

	nowy->firstName = firstName;
	nowy->lastName = lastName;
	nowy->accountNumber = accountNumber;
	nowy->balance = balance;

	if (first == 0) {
		first = nowy;
		last = nowy;
	}
	else {
		first->next = nowy;
		nowy->previous = first;
		nowy->next = 0;
		first = nowy;
	}
}

void Bank::deleteAccount() {
	if (last == 0) {
		std::cout << "There aren't any accounts\n";
		system("pause");
	}
	else {
		BankAccount* temporary = last;
		char decision;
		std::cout << "Would you like to select account by last name or number? [L/N]";
		std::cin >> decision;
		do {
			if (decision == 'l' || decision == 'L') {
				std::string lastName;

				while (temporary) {								// znaczy to samo co while(temporary!=0) wyœwietla po kolei wszystkie konta
					std::cout << temporary->firstName;
					std::cout << "\t";
					std::cout << temporary->lastName;
					std::cout << "\t";
					std::cout << temporary->accountNumber;
					std::cout << "\t";
					std::cout << temporary->balance << "$\n";
					temporary = temporary->next;
				}
				temporary = last;
				std::cout << "Delete account of (type in the last name): ";
				std::cin >> lastName;
				while (lastName != temporary->lastName) {
					temporary = temporary->next;
				}
				temporary->showAccount();
				do {
					std::cout << "\nDelete this account? [Y/N]: ";
					std::cin >> decision;
					if (decision != 'y' && decision != 'n')
						std::cout << "You are supposed to choose Y (yes) or N (no). try again\n";
				} while (decision != 'y' && decision != 'n');
				if (decision == 'y' || decision == 'Y') {
					if (first == last) {
						first = 0;
						last = 0;
					}
					else if (temporary == first) {
						first = first->previous;
						first->next = 0;
					}
					else if (temporary == last) {
						last = last->next;
						last->previous = 0;
					}
					else {
						temporary->previous->next = temporary->next;
						temporary->next->previous = temporary->previous;
					}
					system("pause");
				}
				else {
					std::cout << "\n\nYou decided not to delete this account\n\n ";
					system("pause");
				}
			}
			else if (decision == 'n' || decision == 'N') {
				int number;

				while (temporary) {								// znaczy to samo co while(temporary!=0) wyœwietla po kolei wszystkie konta
					std::cout << temporary->firstName;
					std::cout << "\t";
					std::cout << temporary->lastName;
					std::cout << "\t";
					std::cout << temporary->accountNumber;
					std::cout << "\t";
					std::cout << temporary->balance << "$\n";
					temporary = temporary->next;
				}
				temporary = last;
				std::cout << "Delete account number (type in the account number): ";
				std::cin >> number;
				while (number != temporary->accountNumber) {
					temporary = temporary->next;
				}
				temporary->showAccount();
				do {
					std::cout << "\nDelete this account? [Y/N]: ";
					std::cin >> decision;
					if (decision != 'y' && decision != 'n' && decision != 'Y' && decision != 'N')
						std::cout << "You are supposed to choose Y (yes) or N (no). try again\n";
				} while (decision != 'y' && decision != 'n' && decision != 'Y' && decision != 'N');
				if (decision == 'y' || decision == 'Y') {
					if (first == last) {
						first = 0;
						last = 0;
					}
					else if (temporary == first) {
						first = first->previous;
						first->next = 0;
					}
					else if (temporary == last) {
						last = last->next;
						last->previous = 0;
					}
					else {
						temporary->previous->next = temporary->next;
						temporary->next->previous = temporary->previous;
					}
					system("pause");
				}
				else {
					std::cout << "\n\nYou decided not to delete this account\n\n ";
					system("pause");
				}
			}
			else
				std::cout << "You are supposed to type L (last name) or N (number) letter. Try again\n";
		} while (decision != 'l' && decision != 'n' && decision == 'N' && decision == 'L');
	}
	

	//delete temporary;									<------ dopóki nie usun¹³em tego by³y problemy z displayAllAccounts() gdy wywo³ywa³em to po deleteAccount()
}

void Bank::transfer() {
	if (last == first)
		std::cout << "\n\nunable to make a transfer. There are 0 accounts or only 1\n";
	else {

		BankAccount* temporary = last;

		while (temporary) {								// znaczy to samo co while(temporary!=0) wyœwietla po kolei wszystkie konta
			std::cout<<temporary->firstName;
			std::cout << "\t";
			std::cout << temporary->lastName;
			std::cout << "\t";
			std::cout << temporary->accountNumber;
			std::cout << "\t";
			std::cout << temporary->balance<<"$\n";
			temporary = temporary->next;
		}
		
		std::cout << "\n\ntransfer money from (last name): ";
		std::string giver, receiver;

		std::cin >> giver;

		BankAccount* giverPtr = last;
		while (giver != giverPtr->lastName) {		// ----------------------- wyszukiwanie konta giver
			giverPtr = giverPtr->next;
		}

		std::cout << "\t---> to (last name): ";
		std::cin >> receiver;

		BankAccount* receiverPtr = last;
		while (receiver != receiverPtr->lastName) {		// -----------------------tu bedzie wyszukiwanie konta receiver
			receiverPtr = receiverPtr->next;
		}
		

		std::cout << "\n\nHow much $ do you want to transfer?: ";
		int money;
		do {
			std::cin >> money;
			if (giverPtr->balance < money) {
				std::cout <<"\n"<< giver << " doesn't have that amount of money.\nHow much $ do you want to transfer?: ";
			}
			else if(money<0)
				std::cout << "You are supposed to type in a positive number\nIf you don't want to transfer any money just type 0.\nHow much $ do you want to transfer?: ";
		} while (money < 0 || giverPtr->balance < money); // -----------------------pamietaj ¿eby wstawiæ || money > giver->balance

		giverPtr->withdraw(money);
		receiverPtr->deposit(money);
		std::cout << "\n\nDone :)\n";
		//delete giverPtr;
		//delete receiverPtr;
		//delete temporary;
	}
}

void Bank::displayAllAccounts() {
	BankAccount* temporary = last;
	int counter = 1;
	while (temporary) {								// znaczy to samo co while(temporary!=0)
		std::cout << counter << ".";
		temporary->showAccount();
		temporary = temporary->next;
		counter++;
	}
	std::cout << "\n\nfinished the displayAllAccounts() function\n\n";
	delete temporary;
}

int Bank::howManyAccounts() {
	BankAccount* temporary = last;
	int counter = 0;
	for (temporary = last; temporary; temporary = temporary->next)
		counter++;

	return counter;
}

void Bank::save() {

	std::fstream file;

	file.open("bank_data.txt", std::ios::out);

	if (first == 0)
		std::cout << "\nThere are no accounts to be saved\n";
	else {
		BankAccount* temporary = last;
		while (temporary) {
			file << temporary->firstName << std::endl;
			file << temporary->lastName << std::endl;
			file << temporary->accountNumber << std::endl;
			file << temporary->balance << std::endl;

			temporary = temporary->next;
		}
	}
	file.close();
}

void Bank::load() {
	last = 0;
	first = 0;

	std::fstream file;

	file.open("bank_data.txt", std::ios::in);

	if (file.good() == true) {
		// --------------------instrukcje wczytywania 
		std::string line, fName, lName;
		int aNumber, balance;
		int lineNumber = 1;

		while (getline(file, line)) {
			switch (lineNumber) {
			case 1: 
				fName = line;
				break;
			case 2: 
				lName = line;
				break;
			case 3:
				aNumber = atoi(line.c_str());
				break;
			case 4: 
				balance = atoi(line.c_str());
				break;
			}
			if (lineNumber == 4) {
				newAccount(fName, lName, aNumber, balance);
				lineNumber = 0;
			}
				
			lineNumber++;
		}


	}
	else {
		std::cout << "\nFailed to open bank_data.txt file\n";
	}
	file.close();
}

void Bank::overviewMode() {
	BankAccount* temporary = last;
	if (last == 0) {
		std::cout << "unable to open the overviewMode. There are no accounts...\n";
	}
	else {
		int wybor;
		do {
			system("cls");
			temporary->showAccount();
			std::cout << "\n6.Next | 4.Previous | 8.Deposit | 2.Withdraw | 0.Exit overviewMode\n\tchoose option: ";
			std::cin >> wybor;
			if (wybor == 6) {
				if (temporary->next == 0) {
					std::cout << "\n\tCould't find next account.\n";
					system("pause");
				}
				else
					temporary = temporary->next;
			}
			else if (wybor == 4)
				if (temporary->previous == 0) {
					std::cout << "\n\tCould't find previous account.\n";
					system("pause");
				}
				else
					temporary = temporary->previous;
			else if (wybor == 8)
				temporary->deposit();
			else if (wybor == 2)
				temporary->withdraw();
			else if (wybor == 0) {
			}
			else {
				std::cout << "\n\tThere is no such an option. Try Again...";
				system("pause");
			}
		} while (wybor != 0);
	}
}

int main()		// -------------------------------------------- G³ówna funkcja -----------------------------------------------
{
	Bank* myBank = new Bank;

	int wybor;
	do {
		system("cls");
		std::cout << "   ---------------------------------------------   " << std::endl;
		std::cout << "   ----=======>> The BANK  <<=======---  \n\n";
		std::cout << "   1. Create new bank account  " << std::endl;
		std::cout << "   2. Delete bank account  " << std::endl;
		std::cout << "   3. Transfer money " << std::endl;
		std::cout << "   4. Display all accounts  " << std::endl;
		std::cout << "   5. How many accounts are in the bank?  " << std::endl;
		std::cout << "   6. Save bank data " << std::endl;
		std::cout << "   7. Load saved bank data  " << std::endl;
		std::cout << "   8. Overview mode (with deposit & withdraw functions)  " << std::endl;
		std::cout << "   0. Exit  " << std::endl;
		std::cout << "   ---------------------------------------------   " << std::endl;
		std::cout << "\n   Wybierz numer polecenia :";

		wybor = _getch();                                                     

		if (wybor == 49)    //1
		{
			system("cls");
			myBank->newAccount();
		}
		else if (wybor == 50)   //2
		{
			system("cls");
			myBank->deleteAccount();
		}
		else if (wybor == 51)    //3
		{
			system("cls");
			myBank->transfer();
			system("pause");

		}
		else if (wybor == 52)   //4
		{
			system("cls");
			myBank->displayAllAccounts();
			system("pause");
		}
		else if (wybor == 53)   //5
		{
			if(myBank->howManyAccounts() == 1)
				std::cout << "\n\n There is " << myBank->howManyAccounts() << " account in the bank\n\n";
			else
				std::cout << "\n\n There are "<< myBank->howManyAccounts() <<" accounts in the bank\n\n";
			system("pause");
		}
		else if (wybor == 54)   //6
		{
			myBank->save();
			std::cout << "\nSuccessfully saved bank data in bank_data.txt file\n";
			system("pause");
		}
		else if (wybor == 55)   //7
		{
			myBank->load();
			std::cout << "\nSuccessfully loaded bank data from bank_data.txt file\n";
			system("pause");
		}
		else if (wybor == 56)   //8
		{
			system("cls");
			std::cout << "\n\n overwiew mode \n\n";
			myBank->overviewMode();
			system("pause");
		}
	} while (wybor != 48); //0
	

	delete myBank;

	system("pause");
	return 0;
}