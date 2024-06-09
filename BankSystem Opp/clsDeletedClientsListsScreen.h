#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

class clsDeletedClientsListsScreen : protected clsScreen
{
private:

    static void _PrintClientRecordLine(clsBankClient Client)
    {

        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(8) << left << Client.AccountBalance;
        cout << "| " << setw(12) << left << Client.GetDeletionDate();

    }

public:

	static void ShowDeletedClientsList()
	{

        if (!CheckAccessRights(clsUser::enPermissionValues::eShowDeletedClientLiest))
        {
            return;
        }


		_DrawScreenHeader("\tDeleted Clients List");

		vector <clsBankClient> vDeletedClients = clsBankClient::LoadDeletedClientsDataFromFile();

        cout << setw(8) << left << "" << "\n\t___________________________________________________";
        cout << "___________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(8) << "Balance";
        cout << "| " << left << setw(12) << "DeletionDate";

        cout << setw(8) << left << "" << "\n\t___________________________________________________";
        cout << "___________________________________________________\n" << endl;

        if (vDeletedClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vDeletedClients)
            {

                _PrintClientRecordLine(Client);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t___________________________________________________";
        cout << "___________________________________________________\n" << endl;

	}
};

