#pragma once

#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsAddNewUserScreen: protected clsScreen
{
private:


	static void _PrintClient(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nUser Name     : " << User.UserName;
		cout << "\nFull Name     : " << User.FullName();
		cout << "\nEmail         : " << User.Email;
		cout << "\nPhone         : " << User.Phone;
		cout << "\nPassword      : " << User.Password;
		cout << "\nPermissions   : " << User.Permissions;
		cout << "\n___________________\n";

	}
	static int _ReadPermission()
	{
		char Ansewer = 'n';
		cout << "Do you want to give full access? y/n ";
		cin >> Ansewer;

		int Permission = 0;

		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			return -1;
		}


		cout << "Do you want to give access: " << endl;

		cout << "\nShow Client Liest? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eShowClientLiest;
		}

		cout << "\nShow Deleted Client Liest? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eShowDeletedClientLiest;
		}

		cout << "\nAdd New Client? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eAddNewClient;
		}

		cout << "\nDelete Client? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eDeleteCliet;
		}

		cout << "\nUpdate Client? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eUpdateClientInfo;
		}

		cout << "\nFind Client? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eFindClient;
		}


		cout << "\nTransactions? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eTransactions;
		}

		cout << "\nManage Users? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eManageUsers;
		}


		cout << "\nLogin Register? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eLoginRegister;
		}

		cout << "\nCurrency Exchange? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eCurrencyExchange;
		}

		return Permission;
	}

	static void _ReadUserInfos(clsUser &NewUser)
	{
		cout << "Enter First Name: ";
		NewUser.FirstName = clsInputValidate::ReadString();

		cout << "Enter Last Name: ";
		NewUser.LastName = clsInputValidate::ReadString();

		cout << "Enter Email: ";
		NewUser.Email = clsInputValidate::ReadString();

		cout << "Enter Phone: ";
		NewUser.Phone = clsInputValidate::ReadString();

		cout << "Enter Password: ";
		NewUser.Password = clsInputValidate::ReadString();

		NewUser.Permissions = _ReadPermission();
	}



public:
	static void ShowAddNewUser()
	{
		_DrawScreenHeader("\tAdd New User Screen");

		cout << "Plese Enter User Name: ";

		string UserName ;
		UserName = clsInputValidate::ReadString();
		while (clsUser::IsUserExist(UserName))
		{
			cout << "UserName Is Already Used, Choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfos(NewUser);

		clsUser::enSaveResults SaveResult ;

		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case  clsUser::enSaveResults::svSucceeded:
		{
			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintClient(NewUser);
			break;
		}
		case clsUser::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;

		}
		case clsUser::enSaveResults::svFaildUserExists :
		{
			cout << "\nError account was not saved because account number is used!\n";
			break;

		}
		}
	}
};

