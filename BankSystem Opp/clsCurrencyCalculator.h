#pragma once
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsCurrencyCalculator: protected clsScreen
{
private:
	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n___________________";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nFull Name  : " << Currency.CurrencyName();
		cout << "\nRate       : " << Currency.Rate();
		cout << "\n___________________\n";
	}

public:

	static void ShowCurrencyCalculator()
	{
		_DrawScreenHeader("\t\tCurrency Calculator");

		cout << "Please Enter Countrys Name Or Code, that you want to change from: ";
		string CodeCurrencyFrom = clsInputValidate::ReadString();

		clsCurrency CurrencyFrom = clsCurrency::Find(CodeCurrencyFrom);

		while (CurrencyFrom.IsEmpty())
		{
			cout << "Currency not Found, Please Enter Countrys Name Or Code, that you want to change from: ";
			CodeCurrencyFrom = clsInputValidate::ReadString();
			CurrencyFrom = clsCurrency::Find(CodeCurrencyFrom);
		}
		_PrintCurrencyCard(CurrencyFrom);


		cout << "Please Enter Countrys Name Or Code, that you want to change To: ";

		string CodeCurrencyTo = clsInputValidate::ReadString();

		clsCurrency CurrencyTo = clsCurrency::Find(CodeCurrencyTo);

		while (CurrencyTo.IsEmpty())
		{
			cout << "Currency not Found, Please Enter Countrys Name Or Code, that you want to change To: ";
			CodeCurrencyTo = clsInputValidate::ReadString();
			CurrencyTo = clsCurrency::Find(CodeCurrencyTo);
		}
		_PrintCurrencyCard(CurrencyTo);

		float Amount = 0;
		cout << "Please Enter The Amount of " << CurrencyFrom.CurrencyCode() << " : ";
		Amount = clsInputValidate::ReadFloatNumber();

		cout << endl << Amount << " Of " << CurrencyFrom.CurrencyCode() << " Is: " << CurrencyFrom.Exchange(Amount, CurrencyTo) << " " << CurrencyTo.CurrencyCode() << endl;


	}

};

