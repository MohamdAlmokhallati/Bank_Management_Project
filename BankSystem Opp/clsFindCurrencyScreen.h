#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen:protected clsScreen
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


public :

	static void ShowFindCurrency()
	{
		_DrawScreenHeader("\t\tFind Currency");

		string CountrysNameOrCode;
		cout << "Please Enter Countrys Name Or Code: ";
		CountrysNameOrCode = clsInputValidate::ReadString();
		clsCurrency Currency = clsCurrency::Find(CountrysNameOrCode);

		while (Currency.IsEmpty())
		{
			cout << "Currency not Found, Please Enter Countrys Name Or Code: ";
			CountrysNameOrCode = clsInputValidate::ReadString();
			Currency = clsCurrency::Find(CountrysNameOrCode);
		}

		_PrintCurrencyCard(Currency);

	}
};

