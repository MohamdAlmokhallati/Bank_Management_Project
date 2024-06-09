#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsDeletedClientsListsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "Global.h"

using namespace std;



class clsMainScreen :protected clsScreen
{


private:
    enum enMainMenueOptions {
        eListClients = 1,eDeletedClientsList = 2, eAddNewClient = 3, eDeleteClient = 4,
        eUpdateClient = 5, eFindClient = 6, eShowTransactionsMenue = 7,
        eManageUsers = 8, eCurrencyExchange = 9, eLoginRegister = 10, eExit = 11
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 11]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 11, "Enter Number between 1 to 11? ",1);
        return Choice;
    }

    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\nPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
        //cout << "\nClient List Screen Will be here...\n";
        clsClientListScreen::ShowClientsList();

    }

    static void _ShowDeletedClientsScreen()
    {
        //cout << "Show Deleted Clients Screen will be here";
        clsDeletedClientsListsScreen::ShowDeletedClientsList() ;
    }

    static void _ShowAddNewClientsScreen()
    {
        //cout << "\nAdd New Client Screen Will be here...\n";
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        //cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        //cout << "\nUpdate Client Screen Will be here...\n";
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        //cout << "\nFind Client Screen Will be here...\n";
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        //cout << "\nTransactions Menue Will be here...\n";
        clsTransactionsScreen::ShowTransactionsScreen();
    }

    static void _ShowManageUsersMenue()
    {
        //cout << "\nUsers Menue Will be here...\n";
        clsManageUsersScreen::ShowManageUsersScreen();
    }

    static void _ShowCurrencyExchangeMenue()
    {
        //cout << "\nShow Currency Exchange Menue will be here\n";
        clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMenue();
    }

    static void _ShowLoginRegister()
    {
        //cout << "Show Login Register will be here";
        clsLoginRegisterScreen::LoginRegisterScreen();
    }

    static void _Logout()
    {
        //cout << "\nEnd Screen Will be here...\n";
        CurrentUser = clsUser::Find("", "");
        
    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eDeletedClientsList:
            system("cls");
            _ShowDeletedClientsScreen();
            _GoBackToMainMenue();
            break;
        case enMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eCurrencyExchange:
            system("cls");
            _ShowCurrencyExchangeMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eLoginRegister:
            system("cls");
            _ShowLoginRegister();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eExit:
            system("cls");
            _Logout();
            //Login();

            break;
        }

    }



public:


    static void ShowMainMenue()
    {

        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[01] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[02] Show Deleted Clients List.\n";
        cout << setw(37) << left << "" << "\t[03] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[04] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[05] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[06] Find Client.\n";
        cout << setw(37) << left << "" << "\t[07] Transactions.\n";
        cout << setw(37) << left << "" << "\t[08] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[09] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Login Register.\n";
        cout << setw(37) << left << "" << "\t[11] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    }

};
