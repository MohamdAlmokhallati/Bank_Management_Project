#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsWithdrawScreen:protected clsScreen
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
    static void ShowWithDrawScreen()
    {
        _DrawScreenHeader("\t  Withdraw Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "Please enter Withdraw amount? ";
        float Amount = clsInputValidate::ReadFloatNumber();

        


        char Answer = 'n';
        cout << "Are you Sure you want to Withdraw " << Amount << " y/n ? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client1.Withdraw(Amount)) {
                cout << "\nAmount Withdrawed Successuffly.\n";
                cout << "\nNew Balnce is : " << Client1.AccountBalance;
            }
            else {
                cout << "\nyou don't have enough money to do this Operation" << endl;
                cout << "\nAmount to withdraw is: " << Amount << endl
                    << "Your Balnce is :" << Client1.AccountBalance<<endl;

            }
        }
        else {
            cout << "\nOpraton was cancelled.\n";
        }



    }
};

