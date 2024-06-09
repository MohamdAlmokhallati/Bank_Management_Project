#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateRateScreen: protected clsScreen
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

	static void ShowUpdateRate()
	{
		_DrawScreenHeader("\t\tUpdate Rate");

		cout << "Please Enter Countrys Name Or Code: ";
		string CountrysNameOrCode = clsInputValidate::ReadString();

		clsCurrency Currency = clsCurrency::Find(CountrysNameOrCode);

		while (Currency.IsEmpty())
		{
			cout << "Currency not Found, Please Enter Countrys Name Or Code: ";
			CountrysNameOrCode = clsInputValidate::ReadString();
			Currency = clsCurrency::Find(CountrysNameOrCode);
		}


		_PrintCurrencyCard(Currency);
		cout << "\nPlease Enter New Rate: ";
		float NewRate = clsInputValidate::ReadFloatNumber();

		char Answer = 'n';
		cout << "Are You Sure You want to change the Rate ? Y/N ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Currency.UpdateRate(NewRate);
			_PrintCurrencyCard(Currency);

			cout << "\nRate Changed Successfully\n";
		}
		else {
			cout << "\nThe operation has been cancelled\n";
		}

	}
};

