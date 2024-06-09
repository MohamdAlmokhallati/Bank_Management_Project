#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "Global.h"

using namespace std;
class clsBankClient : public clsPerson
{

private:
    struct sTransferLog;

    enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2};
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    string _DeletionDate = " ";
    bool _MarkForDelete = false;




    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stof(vClientData[6]),vClientData[7]);

    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += clsUtil::EncryptText(Client.PinCode) + Seperator;
        stClientRecord += to_string(Client.AccountBalance) + Seperator;
        stClientRecord += Client._DeletionDate == "" ? " " : Client._DeletionDate;

        return stClientRecord;

    }

    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C.GetMarkForDelte() == false)
                {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    void _WriteDeltedClient()
    {
        fstream MyFile;
        MyFile.open("Deleted Clients.txt",ios::app);

        if (MyFile.is_open())
        {
            _DeletionDate = clsDate::DateToString(clsDate::GetSystemDate());
            MyFile << _ConverClientObjectToLine(*this) << endl;
            MyFile.close();
        }
    }


    string _sTransferLogToString(sTransferLog Infos, string Seperator = "#//#")
    {
        return Infos.TransferDate + Seperator + Infos.Sender + Seperator + Infos.Recipient +
            Seperator + to_string(Infos.Amount) + Seperator + to_string(Infos.NewSenderBalnce) +
            Seperator + to_string(Infos.NewRecipientBalance) + Seperator + Infos.UserName;
    }


    sTransferLog _GetInTransferfos(float Amount, clsBankClient Recipient)
    {
        sTransferLog Infos;

        Infos.TransferDate = clsDate::GetSystemDateToString();
        Infos.Sender = AccountNumber();
        Infos.Recipient = Recipient.AccountNumber();
        Infos.Amount = Amount;
        Infos.NewSenderBalnce = AccountBalance;
        Infos.NewRecipientBalance = Recipient.AccountBalance;
        Infos.UserName = CurrentUser.UserName;


        return Infos;
    }

    void _WriteTransferLog(float Amount, clsBankClient Recipient)
    {

        fstream MyFile;
        MyFile.open("Transfer Log.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << _sTransferLogToString(_GetInTransferfos(Amount, Recipient)) << endl;

        }
        MyFile.close();
    }


public:
    struct sTransferLog
    {
        string TransferDate = "";
        string Sender = "";
        string Recipient = "";
        float Amount = 0;
        float NewSenderBalnce = 0;
        float NewRecipientBalance = 0;
        string UserName = "";

    };


    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance,string DeletionDate="") :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
        _DeletionDate = DeletionDate;
    }



    static  vector <clsBankClient> LoadDeletedClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Deleted Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }


    static  vector <clsBankClient> LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }


    string AccountNumber()
    {
        return _AccountNumber;
    }

    string GetDeletionDate()
    {
        return _DeletionDate;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetMarkForDelte(bool MarkForDelte)
    {
        _MarkForDelete = MarkForDelte;
    }

    bool GetMarkForDelte()
    {
        return _MarkForDelete;
    }
    __declspec(property(get = GetMarkForDelte, put = SetMarkForDelte)) bool MarkForDelte;


    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;



    static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {



        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && clsUtil::DecryptText(Client.PinCode) == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1 ,svFaildAccountNumberExists = 2 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {

            return enSaveResults::svFaildEmptyObject;
        }

        case enMode::UpdateMode:
        {


            _Update();

            return enSaveResults::svSucceeded;

            break;
        }
        case enMode::AddNewMode:
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else {
                _AddNew();
                _Mode = enMode::UpdateMode;

                return enSaveResults::svSucceeded;
            }
            break;

        }


        return enSaveResults::svFaildEmptyObject;
    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    

    bool Delete()
    {
        vector <clsBankClient> OldClients = LoadClientsDataFromFile();

        for (clsBankClient &Client : OldClients)
        {
            if (Client.AccountNumber() == _AccountNumber)
            {
                Client._MarkForDelete = true;
                Client._WriteDeltedClient();
                break;
            }
        }

        _SaveCleintsDataToFile(OldClients);
        
        *this = _GetEmptyClientObject();

        return true;
    }

    static float GetTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::LoadClientsDataFromFile();

        float TotalBalances = 0;

        for (clsBankClient Client : vClients)
        {

            TotalBalances += Client.AccountBalance;
        }

        return TotalBalances;
    }


    void Deposit(float Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool IsWithdrawValid(float Amount)
    {
        return Amount < _AccountBalance;
    }

    bool Withdraw(float Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else {
            _AccountBalance -= Amount;
            Save();
        }
        return true;
    }

    bool Transfer(clsBankClient &Recipient, float Amount)
    {
        _WriteTransferLog(Amount,Recipient);
        if (Withdraw(Amount))
        {
            Recipient.Deposit(Amount);
            
            return true;
        }
        else {
            return false;
        }
    }

    static sTransferLog TransferLogStringToClient(string Line, string Seperator = "#//#")
    {
        vector <string> TransferLog = clsString::Split(Line, Seperator);
        sTransferLog Infos;

        Infos.TransferDate = TransferLog[0];
        Infos.Sender = TransferLog[1];
        Infos.Recipient = TransferLog[2];
        Infos.Amount = stof(TransferLog[3]);
        Infos.NewSenderBalnce = stof(TransferLog[4]);
        Infos.NewRecipientBalance = stof(TransferLog[5]);
        Infos.UserName = TransferLog[6];

        return Infos;

    }

        static vector <sTransferLog> LoadTransferLogFile()
    {
        fstream MyFile;
        vector <sTransferLog> vTransferLogs;
        MyFile.open("Transfer Log.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                vTransferLogs.push_back(TransferLogStringToClient(Line));
            }
            MyFile.close();
        }
        return vTransferLogs;
    }



};
