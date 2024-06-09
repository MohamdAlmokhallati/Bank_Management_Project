#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "clsMainScreen.h"

class clsLoginScreen: protected clsScreen
{
private:

	static bool _Login()
	{
		bool LoginFaild = false;
		short LoginTrials = 3;
		string UserNmae = "";
		string Password = "";
		do
		{
			if (LoginFaild)
			{

				cout << "\nInvlaid Username/Passord!\n";
				cout << "You have " << --LoginTrials << " Trials to Login.\n\n";
			}

			if (LoginTrials < 1)
			{
				cout << "\n\nYou Are Locked after 3 faild trails" << endl;
				return false;
			}

			cout << "User Name: ";
			UserNmae = clsInputValidate::ReadString();

			cout << "Password: ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(UserNmae, Password);

			LoginFaild = CurrentUser.IsEmpty() ;
		} while (LoginFaild);

		CurrentUser.WriteLoginRegisterInfo();
		clsMainScreen::ShowMainMenue();
		return true;



	}


public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tLogin Screen");
		return _Login();
	}

};

