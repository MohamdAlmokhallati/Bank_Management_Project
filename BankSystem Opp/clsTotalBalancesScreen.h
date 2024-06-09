#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"


class clsTotalBalancesScreen :protected clsScreen
{
private:

    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {

        cout << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(40) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.AccountBalance;

    }


	
public:

    static void ShowTotalBalances()
    {
        _DrawScreenHeader("\t  Total Balances");

        vector <clsBankClient> vClients = clsBankClient::LoadClientsDataFromFile();

        cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        int TotalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {
                _PrintClientRecordBalanceLine(Client);
                cout << endl;
            }

        cout << "\n_______________________________________________________"
            << "_________________________________________\n" << endl
            << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
    }


};

