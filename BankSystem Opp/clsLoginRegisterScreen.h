#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>


class clsLoginRegisterScreen: protected clsScreen
{

private:
	static void _PrintUserLoginRegisterLine(clsUser User)
	{

		cout << "| " << setw(40) << left << User.GetEntryDate();
		cout << "| " << setw(15) << left << User.UserName;
		cout << "| " << setw(12) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permissions;


	}



public:
	
	static void LoginRegisterScreen()
	{

        if (!CheckAccessRights(clsUser::enPermissionValues::eLoginRegister))
        {
            return;
        }

        _DrawScreenHeader("\t  Login Register");

        vector <clsUser> vUsers = clsUser::LoadLoginRegisterFile();

        cout << "\n\t\t\t\t\tInfos List (" << vUsers.size() << ") User(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(40) << "Date/time";
        cout << "| " << left << setw(15) << "UserName";
        cout << "| " << left << setw(12) << "Password";
        cout << "| " << left << setw(12) << "Permissions";

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUser& User : vUsers)
            {
                _PrintUserLoginRegisterLine(User);
                cout << endl;
            }

        cout << "\n_______________________________________________________"
            << "_________________________________________\n" << endl;
	}

};

