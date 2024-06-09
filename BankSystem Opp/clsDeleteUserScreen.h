#pragma once

#include <vector>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"


class clsDeleteUserScreen: protected clsScreen
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


public:

	static void ShowDeleteUser()
	{
		_DrawScreenHeader("\t\tDelte User");

		vector <clsUser> vUsers = clsUser::LoadUsersFile();

		cout << "Please Enter User Name: ";
		string UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "User Name is not found,Please Enter User Name: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		_PrintClient(User);

		char Answer = 'n';
		cout << "\n\nAre you sure you want do delte this user? Y/N ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			User.Delete();
			cout << "\nUser Deleted Seccussfully";
			_PrintClient(User);

		}
		else {
			cout << "\nThe operation has been cancelled";
		}

	}
};

