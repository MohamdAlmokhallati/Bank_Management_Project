#pragma once

#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include <string>
#include <vector>
#include <fstream>
#include "clsUtil.h"

class clsUser : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _UserName;
	string _Password;
	string _EntryDate = " ";
	int _Permissions;
	bool _MarkForDelelte = false;


	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{

		fstream MyFile;
		MyFile.open("Users.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsUser C : vUsers)
			{
				if (C.MarkForDeleted() == false)
				{
					DataLine = _ConverUsereObjectToLine(C);
					MyFile << DataLine << endl;
				}

			}

			MyFile.close();

		}

	}

	void _Update()
	{
		vector <clsUser> _vUsers;
		_vUsers = LoadUsersFile();

		for (clsUser& C : _vUsers)
		{
			if (C.UserName == _UserName)
			{
				C = *this;
				break;
			}

		}

		_SaveUsersDataToFile(_vUsers);

	}


	static string _ConverUsereObjectToLine(clsUser User, string Seprator = "#//#")
	{
		string Resutl;
		Resutl += User.FirstName + Seprator;
		Resutl += User.LastName + Seprator;
		Resutl += User.Email + Seprator;
		Resutl += User.Phone + Seprator;
		Resutl += User.UserName + Seprator;
		Resutl += clsUtil::EncryptText(User.Password) + Seprator;
		Resutl += to_string(User.Permissions);
		return Resutl;
	}

	static clsUser LoginRegisterInfoToObject(string Line, string Seprator = "#//#")
	{
		vector <string> User = clsString::Split(Line, Seprator);

		return clsUser(enMode::UpdateMode, User[0], User[1], User[2], stoi(User[3]));
	}


	static clsUser _LineToUserObject(string Line,string Seprator="#//#")
	{
		vector <string> User;
		User = clsString::Split(Line, Seprator);

		return clsUser(enMode::UpdateMode, User[0], User[1], User[2], User[3], User[4], User[5], stoi(User[6]));

	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string _GetLoginRegisterInfo(string Seprator = "#//#")
	{
		return clsDate::GetSystemDateToString() + Seprator + UserName + Seprator + Password + Seprator + to_string(Permissions);
	}

public:

	clsUser(enMode Mode, string EntryDate, string UserName, string Password,
		int Permissions) :
		clsPerson("", "", "", "")
	{
		_EntryDate = EntryDate;
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}


	clsUser(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string UserName, string Password,
		int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}


	enum enPermissionValues {
		eAll=-1,
		eShowClientLiest = 1, eShowDeletedClientLiest = 2,
		eAddNewClient = 4, eDeleteCliet = 8, eUpdateClientInfo = 16, eFindClient = 32,
		eTransactions = 64, eManageUsers = 128,eLoginRegister = 256,eCurrencyExchange = 512
	};




	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}



	bool MarkForDeleted()
	{
		return _MarkForDelelte;
	}

	string GetEntryDate()
	{
		return _EntryDate;
	}


	string GetUserName()
	{
		return _UserName;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserSetUserName))string UserName;


	string GetPassword()
	{
		return _Password;
	}

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword))string Password;



	int GetPermissions()
	{
		return _Permissions;
	}

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions))int Permissions;


	static vector<clsUser> LoadUsersFile()
	{
		vector<clsUser> vUsers;
		fstream MyFile;

		MyFile.open("Users.txt", ios::in); //Read only

		if (MyFile.is_open())
		{
		string Line;
			while (getline(MyFile, Line))
			{
				vUsers.push_back(_LineToUserObject(Line));
			}
			MyFile.close();
		}

		return vUsers;
	}

	static clsUser Find(string UserName)
	{
		vector <clsUser> vUsers = LoadUsersFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == UserName)
			{
				return User;
			}
		}
		return _GetEmptyUserObject();

	}

	static clsUser Find(string UserName,string Password)
	{
		vector <clsUser> vUsers = LoadUsersFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == UserName && clsUtil::DecryptText(User.Password) == Password)
			{
				return User;
			}
		}
		return _GetEmptyUserObject();

	}



	// will return true if the User Exists
	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConverUsereObjectToLine(*this));
	}


	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		}

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;

			break;
		}

		case enMode::AddNewMode:
		{
			//This will add new record to file or database
			if (clsUser::IsUserExist(_UserName))
			{
				return enSaveResults::svFaildUserExists;
			}
			else
			{
				_AddNew();
				//We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}
		}
		return enSaveResults::svFaildEmptyObject;
	}

	bool Delete()
	{
		vector <clsUser> vUsers = LoadUsersFile();
		for (clsUser& U : vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkForDelelte = true;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);

		*this = _GetEmptyUserObject();

		return true;
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool CheckAccessPermission(enPermissionValues PermissionValues)
	{
		if (this->Permissions == enPermissionValues::eAll)
			return true;

		if ((PermissionValues & this->Permissions) == PermissionValues)
			return true;
		else
			return false;

	}

	static vector <clsUser> LoadLoginRegisterFile()
	{
		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile,Line))
			{
				vUsers.push_back(LoginRegisterInfoToObject(Line));
			}
		}
		return vUsers;
	}


	void WriteLoginRegisterInfo()
	{
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);


		if (MyFile.is_open())
		{
			MyFile << _GetLoginRegisterInfo() << endl;
			MyFile.close();
		}
	}



};

