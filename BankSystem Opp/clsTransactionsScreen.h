#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"


class clsTransactionsScreen : protected clsScreen
{
private:
    enum enTransactionMenueOptions
    {
        eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4,
        eTransferLog = 5,eMainMenue = 6
    };

    static short _ReadTransactionMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ", 1);
        return Choice;
    }

    static void _ShowDepositScreen()
    {
        //cout << "Show DepositScreen will be here"<<endl;
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        //cout << "Show Withdraw Screen will be here" << endl;
        clsWithdrawScreen::ShowWithDrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        //cout << "Show Total Balances Screen will be here" << endl;
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _ShowTransferScreen()
    {
        //cout << "\nTransfer will be here\n";
        clsTransferScreen::ShowTransfer();
    }

    static void _ShowTransferLogScreen()
    {
        //cout << "\nShow Transfer Log Screen will be here\n";
        clsTransferLogScreen::ShowTransferLog();
    }

    static  void _GoBackToTransactionMenue()
    {
        cout << setw(37) << left << "" << "\nPress any key to go back to Transaction Menue...\n";

        system("pause>0");
        ShowTransactionsScreen();
    }



    static void _PerfromTransactionMenueOption(enTransactionMenueOptions TransactionMenueOptions)
    {
        switch (TransactionMenueOptions)
        {
        case clsTransactionsScreen::eDeposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionMenue();
            break;
        case clsTransactionsScreen::eWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionMenue();
            break;

        case clsTransactionsScreen::eTotalBalances:
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionMenue();
            break;
        case clsTransactionsScreen::eTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionMenue();
            break;
        case clsTransactionsScreen::eTransferLog:
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionMenue();
            break;
        case clsTransactionsScreen::eMainMenue:

            //do Nothing Here :-);

            break;

        default:
            system("cls");
            cout << "Error, Pleas Try agin :-(" << endl;
            break;
        }
    }

public:

	static void ShowTransactionsScreen()
	{

		system("cls");


        if (!CheckAccessRights(clsUser::enPermissionValues::eTransactions))
        {
            return;
        }


		_DrawScreenHeader("\tTransaction Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tTransaction Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";

        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromTransactionMenueOption( (enTransactionMenueOptions) _ReadTransactionMenueOption() );
	}
};

