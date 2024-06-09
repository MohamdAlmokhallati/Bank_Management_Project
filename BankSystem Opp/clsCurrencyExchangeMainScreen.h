#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculator.h"
#include <iomanip>



class clsCurrencyExchangeMainScreen:protected clsScreen
{
private:
    enum enCurrencyExchangeOptions
    {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3,
        eCurrencyCalculator = 4, eMainMenue = 5
    };

    static short _ReadCurrencyExchangeMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ", 1);
        return Choice;
    }


    static void _GoBackToCurrencyExchangeMenue()
    {
        cout << setw(37) << left << "" << "\nPress any key to go back to Transaction Menue...\n";

        system("pause>0");
        ShowCurrencyExchangeMenue();
    }

    static void _ShowListCurrencies()
    {
        //cout << "\n List Currencies will be here\n";
        clsListCurrenciesScreen::ShowListCurrencies();
    }

    static void _ShowFindCurrency()
    {
        //cout << "\n Find Currency will be here\n";
        clsFindCurrencyScreen::ShowFindCurrency();
    }

    static void _ShowUpdateRate()
    {
        //cout << "\nUpdate Rate will be here\n";
        clsUpdateRateScreen::ShowUpdateRate();
    }

    static void _ShowCurrencyCalculator()
    {
        //cout << "\nCurrency Calculator will be here\n";
        clsCurrencyCalculator::ShowCurrencyCalculator();
    }




    static void _PerfromCurrencyExchangeOptions(enCurrencyExchangeOptions CurrencyExchangeOptions)
    {
        switch (CurrencyExchangeOptions)
        {
        case clsCurrencyExchangeMainScreen::eListCurrencies:
            system("cls");
            _ShowListCurrencies();
            _GoBackToCurrencyExchangeMenue();
            break;
        case clsCurrencyExchangeMainScreen::eFindCurrency:
            system("cls");
            _ShowFindCurrency();
            _GoBackToCurrencyExchangeMenue();
            break;
        case clsCurrencyExchangeMainScreen::eUpdateRate:
            system("cls");
            _ShowUpdateRate();
            _GoBackToCurrencyExchangeMenue();
            break;
        case clsCurrencyExchangeMainScreen::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculator();
            _GoBackToCurrencyExchangeMenue();
            break;
        case clsCurrencyExchangeMainScreen::eMainMenue:
            //Do Nothing the stack will get the User back
            break;
        default:
            break;
        }
    }



public:

	static void ShowCurrencyExchangeMenue()
	{
		system("cls");

        if (!CheckAccessRights(clsUser::enPermissionValues::eCurrencyExchange))
        {
            return;
        }


		_DrawScreenHeader("\t\tCurrency Exchange");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Echange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";

        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromCurrencyExchangeOptions((enCurrencyExchangeOptions)_ReadCurrencyExchangeMenueOption());
	}

};

