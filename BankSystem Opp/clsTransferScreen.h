#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


class clsTransferScreen:protected clsScreen
{
private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "Client Card: \n";
		cout << "____________________" << endl;
		cout << "Full Name     :" << Client.FullName() << endl;
		cout << "Acc. Number   :" << Client.AccountNumber() << endl;
		cout << "Balance       :" << Client.AccountBalance << endl;
		cout << "____________________" << endl;

	}


public:
	static void ShowTransfer()
	{
		_DrawScreenHeader("\tTransfer Screen");

		string SenderAccountNumber;
		cout << "Please Enter Account Number to Transfer From: ";
		SenderAccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(SenderAccountNumber))
		{
			cout << "Client is not Found, Please Enter Account Number to Transfer From: ";
			SenderAccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Sender = clsBankClient::Find(SenderAccountNumber);
		_PrintClient(Sender);



		string RecipientAccountNumber;
		cout << "Please Enter Account Number to Transfer To: ";
		RecipientAccountNumber = clsInputValidate::ReadString();


		while (!clsBankClient::IsClientExist(RecipientAccountNumber) || RecipientAccountNumber == SenderAccountNumber)
		{
			cout << "Client is not Found, Please Enter Account Number to Transfer To: ";
			RecipientAccountNumber = clsInputValidate::ReadString();
			
		}

		clsBankClient Recipient = clsBankClient::Find(RecipientAccountNumber);
		_PrintClient(Recipient);

		float Amount = 0;
		cout << "Enter Transfer Amount: ";
		Amount = clsInputValidate::ReadFloatNumber();



		if (!Sender.IsWithdrawValid(Amount)) {
			cout << "There is not enough money for the operation" << endl;
			return;
		}

		char Answer = 'n';
		cout << "Are You Sure you want to do this operation ? Y/N ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (Sender.Transfer(Recipient, Amount))
			{
				cout << "operation accomplished successfully" << endl;

				_PrintClient(Sender);
				_PrintClient(Recipient);
			}
			else {
				cout << "There is not enough money for the operation" << endl;
			}
		}
		else {
			cout << "Operation is Cancelled" << endl;
		}


	}
};

