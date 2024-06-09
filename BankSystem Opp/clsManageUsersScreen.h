#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen:protected clsScreen
{
private:

    enum enUsersMenueOptions {
        eUsersList = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4,
        eFindUser = 5, eMainMenue = 6
    };


    static short _ReadUserMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ", 1);
        return Choice;
    }

    static  void _GoBackToUserMenue()
    {
        cout << setw(37) << left << "" << "\nPress any key to go back to Users Menue...\n";

        system("pause>0");
        ShowManageUsersScreen();
    }


    static void _ShowUsersList()
    {
        //cout << "Users List will be here";
        clsUsersListScreen::ShowUsersList();
    }

    static void _ShowAddNewUser()
    {
        //cout << "Add New User will be here";
        clsAddNewUserScreen::ShowAddNewUser();
    }

    static void _ShowDeleteUser()
    {
        //cout << "Delete User will be here";
        clsDeleteUserScreen::ShowDeleteUser();
    }

    static void _ShowUpdateUser()
    {
        //cout << "Update User will be here";
        clsUpdateUserScreen::ShowUpdateUser();
    }

    static void _ShowFindUser()
    {
        //cout << "Find User will be here";
        clsFindUserScreen::ShowFindUser();
    }


    static void _PerfromUsersMenueOption(enUsersMenueOptions UsersMenueOption)
    {
        switch (UsersMenueOption)
        {
        case clsManageUsersScreen::eUsersList:
            system("cls");
            _ShowUsersList();
            _GoBackToUserMenue();
            break;
        case clsManageUsersScreen::eAddNewUser:
            system("cls");
            _ShowAddNewUser();
            _GoBackToUserMenue();
            break;
        case clsManageUsersScreen::eDeleteUser:
            system("cls");
            _ShowDeleteUser();
            _GoBackToUserMenue();
            break;
        case clsManageUsersScreen::eUpdateUser:
            system("cls");
            _ShowUpdateUser();
            _GoBackToUserMenue();
            break;
        case clsManageUsersScreen::eFindUser:
            system("cls");
            _ShowFindUser();
            _GoBackToUserMenue();
            break;
        case clsManageUsersScreen::eMainMenue:
            //just do nothing it will let the User back
            break;
        default:
            cout << "Sorry Somthing went wrong, try agin pleas"<<endl;
            break;
        }
    }

public:



	static void ShowManageUsersScreen()
	{
        system("cls");


        if (!CheckAccessRights(clsUser::enPermissionValues::eManageUsers))
        {
            return;
        }


		_DrawScreenHeader("\tManage Users Screen", "\t    Users Menue");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tUsers Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Users List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerfromUsersMenueOption((enUsersMenueOptions)_ReadUserMenueOption());
	}
};

