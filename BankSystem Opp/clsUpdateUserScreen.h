#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"


class clsUpdateUserScreen:protected clsScreen
{
private:


	static void _PrintUser(clsUser &User)
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

		cout << "Show Client Liest? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eShowClientLiest;
		}

		cout << "Show Deleted Client Liest? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eShowDeletedClientLiest;
		}

		cout << "Add New Client? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eAddNewClient;
		}

		cout << "Delete Client? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eDeleteCliet;
		}

		cout << "Update Client? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eUpdateClientInfo;
		}

		cout << "Find Client? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eFindClient;
		}


		cout << "Transactions? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eTransactions;
		}

		cout << "Manage Users? y/n ";
		cin >> Ansewer;
		if (Ansewer == 'Y' || Ansewer == 'y')
		{
			Permission += (int)clsUser::enPermissionValues::eManageUsers;
		}


		cout << "Login Register? y/n ";
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

	static void _ReadUserInfos(clsUser& NewUser)
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
 	static void ShowUpdateUser()
	{
		_DrawScreenHeader("\t  Update User");

		string UserName;
		cout << "Please enter User Name: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "User Name is not found, Please enter User Name: ";
			UserName = clsInputValidate::ReadString();

		}

		clsUser User = clsUser::Find(UserName);

		_PrintUser(User);

		cout << "\n\nUpdate User Info:";
		cout << "\n____________________\n\n";

		_ReadUserInfos(User);

		clsUser::enSaveResults SaveResult;
		SaveResult = User.Save();

		switch (SaveResult)
		{
		case  clsUser::enSaveResults::svSucceeded:
		{
			cout << "\nUser Updated Successfully :-)\n";
			_PrintUser(User);
			break;
		}
		case clsUser::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;

		}

		}

		

	}
};

