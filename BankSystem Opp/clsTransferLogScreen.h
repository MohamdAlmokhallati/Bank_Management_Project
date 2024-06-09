#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>



class clsTransferLogScreen:protected clsScreen
{
private:

	static void _PrintTransferLogLine(clsBankClient::sTransferLog TransferLog)
	{

		cout << "| " << setw(30) << left << TransferLog.TransferDate;
		cout << "| " << setw(12) << left << TransferLog.Sender;
		cout << "| " << setw(12) << left << TransferLog.Recipient;
		cout << "| " << setw(12) << left << TransferLog.Amount;
        cout << "| " << setw(12) << left << TransferLog.NewSenderBalnce;
        cout << "| " << setw(12) << left << TransferLog.NewRecipientBalance;
        cout << "| " << setw(12) << left << TransferLog.UserName;

	}



public:
	static void ShowTransferLog()
	{
		_DrawScreenHeader("\t\tTransfer Log");

       vector <clsBankClient::sTransferLog> vTransferLogs = clsBankClient::LoadTransferLogFile();

        cout << "\n\t\t\t\t\tInfos List (" << vTransferLogs.size() << ") User(s).";
        cout << "\n________________________________________________________";
        cout << "________________________________________________________\n" << endl;

        cout << "| " << left << setw(30) << "Date/time";
        cout << "| " << left << setw(12) << "s.Acct";
        cout << "| " << left << setw(12) << "d.Acct";
        cout << "| " << left << setw(12) << "Amount";
        cout << "| " << left << setw(12) << "s.Balance";
        cout << "| " << left << setw(12) << "d.Balance";
        cout << "| " << left << setw(12) << "User";



        cout << "\n________________________________________________________";
        cout << "________________________________________________________\n" << endl;

        if (vTransferLogs.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsBankClient::sTransferLog& TransferLog : vTransferLogs)
            {
                _PrintTransferLogLine(TransferLog);
                cout << endl;
            }

        cout << "\n________________________________________________________"
            << "________________________________________________________\n" << endl; 

	}
};

