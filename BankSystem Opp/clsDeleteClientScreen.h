#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
class clsDeleteClientScreen : protected clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;

        cout << "\n___________________\n";

    }

public:


    static void ShowDeleteClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissionValues::eDeleteCliet))
        {
            return;
        }


        _DrawScreenHeader("\tDelete Client Screen");


        cout << "\nPlease Enter The Account Number :\n";
        string AccountNumber = clsInputValidate::ReadString();


        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number Is Not Foun, Choose another one:";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        char UserAnswer = 'n';
        cout << "\nAre You Shore you want to delete This User? Y/N ";
        cin >> UserAnswer;
        if (UserAnswer == 'Y' || UserAnswer == 'y')
        {
            if (Client.Delete())
            {
                cout << "Client Deleted Successuflly" << endl;
                _PrintClient(Client);
            }
            else {
                cout << "Error Please Try Agin :-(" << endl;
            }
        }

    }






};

