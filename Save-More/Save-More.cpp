//Assignment #3 Save-More
//Name: Michael Cohen
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
using namespace std;

class BankAccount
{
protected:
	char *accountType;
	double currentBalance;
	double interestRate;

public:
	virtual int depositFunds(double depositAmount);
	virtual int withdrawFunds(double withdrawAmount);
	virtual void displayInfo();
};
//NO ACCOUNT CAN GO BELOW 0!!!!!!!!
int BankAccount::depositFunds(double depositAmount)		//deposit function
{
	if (depositAmount >= 0)
	{
		currentBalance += depositAmount;
		return 0;
	}
	else
	{
		return -1;
	}
}

int BankAccount::withdrawFunds(double withdrawAmount)		//withdrawal function
{
	if (currentBalance - withdrawAmount > 0)
	{
		currentBalance -= withdrawAmount;
		return 0;
	}
	else
	{
		return -1;
	}
}

void BankAccount::displayInfo()
{
	cout << "Type of Account: " << accountType << endl;
	cout << "Interest Rate: " << (interestRate * 100) << "%" << endl;
	printf("Current Balance: %5.2f\n\n", currentBalance);

}

class SavingsAccount : public BankAccount
{
	//'currentBalance' under $10,000 earns 1% APR & over $10,000 earns 2% APR
	//withdrawls are charged a fee of $2, deducted from 'currentBalance'
public:
	SavingsAccount() //constructor
	{
		accountType = "Savings";
		
	}
	void compoundInterest(bool option)
	{
		if (currentBalance >= 10000)
		{
			interestRate = 0.02;
		}
		else
		{
			interestRate = 0.01;
		}

		if (option == true)
		{
			currentBalance += (currentBalance * (interestRate/12));
		}
	}
	void depositSavings(double depositAmount)
	{
		int option;
		option = BankAccount::depositFunds(depositAmount); //derived 'depositFunds' function from 'BankAccount' Base Class
		if (option == 0)
		{
			if (currentBalance >= 10000)
			{
				interestRate = 0.02;
			}
			else
			{
				interestRate = 0.01;
			}
		}
		else
		{
			cout << "Sorry, Not a valid input!" << endl;
		}

	}
	void withdrawSavings(double withdrawAmount)
	{
		int option;
		option = BankAccount::withdrawFunds(withdrawAmount); //derived 'withdrawFunds' function from 'BankAccount' Base Class
		if (option == 0)
		{
			currentBalance -= 2;					// charged fee ($2)
			if (currentBalance >= 10000)
			{
				interestRate = 0.02;
			}
			else
			{
				interestRate = 0.01;
			}
		}
		else
		{
			cout << "Sorry, you do not have sufficient funds to complete transaction!" << endl;
			currentBalance += withdrawAmount;
		}
	}

};

class CheckingAccount : public BankAccount
{
	//if currentBalance drops below $500 a fee of $5.00 is deducted
	//No interest
	//order checks for $15
public:
	CheckingAccount() //constructor
	{
		accountType = "Checking";
	}
	void orderChecks()
	{
		currentBalance -= 15.00;
		cout << "Checks Ordered! -$15.00 from your Checking Account" << endl;
		printf("Current Balance: %5.2f\n", currentBalance);
	}
	void depositChecking(double depositAmount)
	{
		int option;
		option = BankAccount::depositFunds(depositAmount); //derived 'depositFunds' function from 'BankAccount' Base Class
		if (option == 0)
		{
			if (currentBalance < 500)
			{
				currentBalance -= 5;
			}
		}
		else
		{
			cout << "Sorry, Not a valid input!" << endl;
		}
	}
	void withdrawChecking(double withdrawAmount)
	{
		int option;
		option = BankAccount::withdrawFunds(withdrawAmount); //derived 'withdrawFunds' function from 'BankAccount' Base Class
		if (option == 0)
		{
			if (currentBalance < 500)
			{
				currentBalance -= 5;
			}
		}
		else
		{
			cout << "Sorry, you do not have sufficient funds to complete transaction!" << endl;
		}
	}

};

class CertificateOfDeposit : public BankAccount //set on account creation and can't be updated
{
	//10% with 5 year term and 5% anything less
	//compounded interest which is added to 'currentBalance'
	//10% fee on entire pre-withdrawal balance
	int term;
public:
	CertificateOfDeposit(int termAmount) //constructor
	{
		accountType = "Certificate of Deposit";
		term = termAmount;
	}

	void compoundInterest(bool option)
	{
		if (option == true)
		{
			currentBalance = currentBalance + ((interestRate/12)* currentBalance);
		}
	}
	void depositCD(double depositAmount, int termAmount)
	{
		int option;
		option = BankAccount::depositFunds(depositAmount); //derived 'depositFunds' function from 'BankAccount' Base Class
		if (option == 0)
		{
			term = termAmount;
			if (term <= 5)
			{
				interestRate = 0.05;
			}
			else
			{
				interestRate = 0.10;
			}
		}

	}
	void withdrawCD(double withdrawAmount)
	{

		int option;
		//take fee from pre-withdraw balance
		currentBalance = currentBalance - (currentBalance * 0.10);
		
		option = BankAccount::withdrawFunds(withdrawAmount); //derived 'withdrawFunds' function from 'BankAccount' Base Class
		if (term <= 5)
		{
			interestRate = 0.05;
		}
		else
		{
			interestRate = 0.10;
		}
	}
};


int main()
{
	//variable declarations
	int accountNumber;
	int checkDeposit;
	int saveDeposit;
	int startCD;
	int depositIntoCD;
	char compoundInterest;
	int checkWithdraw;
	int saveWithdraw;
	int cdWithdraw;

	//I may have gone overboard with the 'cin.clear()' and 'cin.ignore()' statements
	cout << "Please Enter your Account Number: " << endl;	
	cin >> accountNumber;
	cin.clear();
	cin.ignore();

	//for Savings
	SavingsAccount mySavings;
	cout << "How much would you like to deposit into your Savings Account?" << endl;
	cin >> checkDeposit;
	cin.clear();
	cin.ignore();
	mySavings.depositSavings(checkDeposit);

	//for Checking
	CheckingAccount myChecking;
	cout << "How much would you like to to deposit into your Checking Account?" << endl;
	cin >> saveDeposit;
	cin.clear();
	cin.ignore();
	myChecking.depositChecking(saveDeposit);

	//for CD
	cout << "How LONG would you like to hold the CD? (enter # of years)" << endl;
	cin >> startCD;
	cin.clear();
	cin.ignore();
	CertificateOfDeposit myCD(startCD);
	cout << "How much would you like to deposit into your CD?" << endl;
	cin >> depositIntoCD;
	cin.clear();
	cin.ignore();
	myCD.depositCD(depositIntoCD, startCD);

	//Display attributes for Each Account
	cout << "------------------------------" << endl;
	cout << "Current Account Summary:\n" << endl;
	cout << "Account Number: " << accountNumber << "\n" << endl;
	mySavings.displayInfo();
	myChecking.displayInfo();
	myCD.displayInfo();
	cout << "------------------------------" << endl;

	//Calculate Monthly Interest for Savings & CD Account
	mySavings.compoundInterest(true);
	myCD.compoundInterest(true);

	//Display After compounding Interest
	cout << "-------------------------------------------------------" << endl;
	cout << "Savings & CD after Compounding A Month of Interest:\n" << endl;
	mySavings.displayInfo();
	myCD.displayInfo();
	cout << "-------------------------------------------------------" << endl;
	
	//Order Checks
	myChecking.orderChecks();	
	
	//Withdraw from Checking and Savings
	cout << "How much would you like to withdraw from your Checking Account?" << endl;
	cin >> checkWithdraw;
	cin.clear();
	cin.ignore();
	myChecking.withdrawChecking(checkWithdraw);
	cout << "How much would you like to withdraw from your Savings Account? ($2 fee for withdrawals)" << endl;
	cin >> saveWithdraw;
	cin.clear();
	cin.ignore();
	mySavings.withdrawSavings(saveWithdraw);

	//Perform early withdrawal for CD
	cout << "How much would you like to take out of your CD? (10% fee on pre-withdrawal balance)" << endl;
	cin >> cdWithdraw;
	cin.clear();
	cin.ignore();
	myCD.withdrawCD(cdWithdraw);

	//Get and display each account status 
	cout << "==============================================" << endl;
	cout << "Final Summary: \n" << endl;
	cout << "Account Number: " << accountNumber << "\n" << endl;
	mySavings.displayInfo();
	myChecking.displayInfo();
	myCD.displayInfo();
	cout << "==============================================" << endl;

	return 0;
}